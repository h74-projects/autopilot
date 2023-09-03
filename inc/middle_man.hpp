#ifndef MIDDLE_MAN_HPP
#define MIDDLE_MAN_HPP

#include "client.hpp"
#include "blocking_queue.hpp"

#include <string> // std string
#include <memory> // unique ptr
#include <chrono> // clocks and durations
#include <cstdint> //uint64_t
#include <thread> // std::thread
#include <atomic> //atomic bool

namespace fgear {

class MiddleMan {
public:
    // frequency in milliseconds
    MiddleMan(std::unique_ptr<Client>&& a_client, uint16_t a_port, std::string const& a_address = "127.0.0.1", uint64_t const& a_frequency = 250);
    ~MiddleMan();

    void send_message(std::string const& a_message);

private:
    void handle_messages();

private:
    thread::BlockingQueue<std::string> m_messages;
    std::unique_ptr<Client> m_client;
    std::chrono::time_point<std::chrono::steady_clock> m_elapsed;
    std::atomic_bool m_active;
    std::thread m_listener;
    uint64_t m_frequency;
};

} // namespace fgear

#endif // MIDDLE_MAN_HPP