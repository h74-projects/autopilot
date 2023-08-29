#include "server_udp.hpp"

namespace fgear {

UdpServer::UdpServer(std::shared_ptr<Protocol> a_protocol, uint32_t const& a_port)
: Server{a_protocol,a_port}
{
}

void UdpServer::connect(std::string const& a_address)
{
    Poco::Net::SocketAddress sock_adr{a_address, m_port};
    m_socket.bind(sock_adr);
    m_socket.connect(sock_adr);
}

void UdpServer::start_listening()
{
    m_listening = true;
    m_listener = std::thread{[this]{recieve_data();}};
}

void UdpServer::recieve_data()
{
    while(m_listening) {
        Poco::Net::SocketAddress sock_adr{};
        int recieved_bytes = m_socket.receiveFrom(reinterpret_cast<void*>(m_buffer), BUFFER_SIZE, sock_adr);
        if (recieved_bytes > 0) {
            std::string message{m_buffer, recieved_bytes};
            m_protocol.get()->unpack(message);
        }
    }
}

} // namespace fgear
