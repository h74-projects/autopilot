#include "client_telnet.hpp"

namespace fgear {

TelnetClient::TelnetClient()
: m_connected{false}
{
}

TelnetClient::~TelnetClient()
{
    m_socket.close();
}

void TelnetClient::connect(std::string const& a_address, uint16_t a_port)
{
    //TODO: add disconnect
    if (m_connected) {
        throw std::runtime_error("already connected");
    }
    m_connected = true;
    Poco::Net::SocketAddress sock_addr{a_address,a_port};
    m_socket.connect(sock_addr);
}


bool TelnetClient::send(std::string const& a_message)
{
    if (not m_connected) {
        return false;
    }
    m_socket.sendMessage(a_message);
    std::string answer = recieve();
    return true;
}

std::string TelnetClient::recieve() 
{
    int len = m_socket.receiveRawBytes(reinterpret_cast<void*>(m_buffer), 4096);
    if (len < 0) {
        throw std::runtime_error("could not recieve message");
    }
    return std::string{m_buffer, static_cast<size_t>(len)};
}


} // namespace fgear
