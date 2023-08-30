#ifndef SERVER_UDP_HPP
#define SERVER_UDP_HPP

#include "server.hpp"

#include "Poco/Net/SocketAddress.h" // socket address class
#include "Poco/Net/Socket.h" // socket class
#include "Poco/Net/DatagramSocket.h" // udp socket

#include <vector> // socketBuff
#include <atomic> // atomic bool
#include <thread> // std::thread

namespace fgear {

constexpr size_t BUFFER_SIZE = 4096;
//TODO: make timeout customizable
constexpr size_t POLLING_TIME_OUT = 200'000;

class UdpServer : public Server {
public:
    explicit UdpServer(uint16_t const& a_port);
    ~UdpServer();

    UdpServer(UdpServer const&) = delete;
    UdpServer& operator=(UdpServer const&) = delete;

    UdpServer(UdpServer&&) = delete;
    UdpServer& operator=(UdpServer&&) = delete;

    void connect(std::string const& a_address = "127.0.0.1") override;

    void start_listening(std::shared_ptr<Protocol> a_protocol) override;

    void stop_listening();

private:
    void recieve_data(std::shared_ptr<Protocol> a_protocol);

private:
    Poco::Net::DatagramSocket m_socket;
    char m_buffer[BUFFER_SIZE];
    std::thread m_listener;
    std::atomic_bool m_listening;

};

} // namespace fgear

#endif // SERVER_UDP_HPP