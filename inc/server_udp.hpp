#ifndef SERVER_UDP_HPP
#define SERVER_UDP_HPP

#include "server.hpp"

#include "Poco/Net/SocketAddress.h" // socket address class
#include "Poco/Net/Socket.h" // socket class
#include "Poco/Net/DatagramSocket.h" // udp socket

#include <vector> // socketBuff
#include <atomic> // atomic bool

namespace fgear {

constexpr size_t BUFFER_SIZE = 4096;

class UdpServer : public Server {
public:
    UdpServer(std::shared_ptr<Protocol> a_protocol, uint32_t const& a_port);
    ~UdpServer();

    UdpServer(UdpServer const&) = delete;
    UdpServer& operator=(UdpServer const&) = delete;

    UdpServer(UdpServer&&) = delete;
    UdpServer& operator=(UdpServer&&) = delete;

    void connect(std::string const& a_address = "127.0.0.1") override;

    void start_listening() override;

private:
    void recieve_data();

private:
    Poco::Net::DatagramSocket m_socket;
    Poco::Net::SocketBufVec m_buffer;
    std::atomic_bool m_listening;


};

} // namespace fgear

#endif // SERVER_UDP_HPP