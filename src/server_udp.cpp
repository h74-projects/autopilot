#include "server_udp.hpp"

namespace fgear {

UdpServer::UdpServer(uint16_t const& a_port)
: Server{a_port}
{
}

UdpServer::~UdpServer()
{
    stop_listening();
    m_socket.close();
}

void UdpServer::connect(std::string const& a_address)
{
    Poco::Net::SocketAddress sock_adr{a_address, m_port};
    m_socket.bind(sock_adr);
    m_socket.connect(sock_adr);
}

void UdpServer::start_listening(std::shared_ptr<Protocol> a_protocol)
{
    if (m_listening) {
        throw std::invalid_argument("server already listening");
    }
    auto lambda = [this](std::shared_ptr<Protocol> protocol) {
        recieve_data(protocol);
    };
    m_listening = true;
    m_listener = std::thread{lambda, a_protocol};
}

void UdpServer::stop_listening()
{
    if (m_listening) {
        m_listening = false;
        m_listener.join();        
    }
}

void UdpServer::recieve_data(std::shared_ptr<Protocol> a_protocol)
{
    while(m_listening) {
        Poco::Net::SocketAddress sock_adr{};
        int recieved_bytes = m_socket.receiveFrom(reinterpret_cast<void*>(m_buffer), BUFFER_SIZE, sock_adr);
        if (recieved_bytes > 0) {
            std::string message{m_buffer, static_cast<size_t>(recieved_bytes)};
            a_protocol.get()->unpack(message);
        } else {
            throw std::runtime_error("could not recieve message");
        }
    }
}

} // namespace fgear
