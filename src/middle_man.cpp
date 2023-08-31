#include "middle_man.hpp"

namespace fgear {

MiddleMan::MiddleMan(std::unique_ptr<Client>&& a_client, uint16_t a_port, std::string const& a_address, uint64_t const& a_frequency)
: m_messages{128}
, m_client{std::move(a_client)}
, m_elapsed{std::chrono::steady_clock::now()}
, m_active{true}
, m_frequency{a_frequency} 
{
    auto lambda = [this]{
        handle_messages();
    };
    m_client.get()->connect(a_address, a_port);
    m_listener = std::thread{lambda};
}

MiddleMan::~MiddleMan()
{
    m_active = false;
    m_listener.join();
}

void MiddleMan::send_message(std::string const& a_message)
{
    m_messages.enqueue(a_message);
}

void MiddleMan::handle_messages()
{
    while (m_active) {
        auto time = m_elapsed - std::chrono::steady_clock::now();
        uint64_t elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(time).count();
        if (not m_messages.empty() && elapsed >= m_frequency) {
            std::string message;
            m_messages.dequeue(message);
            m_client.get()->send(message);
            m_elapsed = std::chrono::steady_clock::now();
        }
    }
}

} // namespace fgear
