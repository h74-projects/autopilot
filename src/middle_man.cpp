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
        if (not m_messages.empty()) {
            std::string message;
            m_messages.dequeue(message);
            if (not m_client.get()->send(message)) {
                throw std::runtime_error("could not send message");
            }
        }
    }
}

} // namespace fgear
