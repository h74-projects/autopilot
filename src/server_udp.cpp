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

} // namespace fgear
