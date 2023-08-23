#include "telnet_client.hpp"

#include <string.h> // memset
#include <netinet/in.h> // sockaddr_in
#include <sys/socket.h> // socket
#include <unistd.h>// close
#include <arpa/inet.h> //inet_pton

#include <exception> // exception
#include <stdexcept> // std exceptions

namespace fgear {

namespace {
    
bool connect_to_telnet(int32_t const& m_socket, std::string const& a_address, uint32_t a_port)
{
    struct sockaddr_in serv_addr;
    memset(&serv_addr,0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(a_port);
    if (inet_pton(AF_INET, a_address.c_str(), &serv_addr.sin_addr) <= 0) {
        
        return false;
    }

    if (connect(m_socket, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        return false;
    }

    return true;    
}

} // namespace

TelnetClient::TelnetClient(std::string const& a_address, uint32_t a_port)
: m_socket(-1)
, m_connected(false)
, m_timeout(1)
{
    m_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (m_socket < 0) {
        throw std::runtime_error("could not open socket");
    }

    if (not connect_to_telnet(m_socket, a_address, a_port)) {
        close();
        throw std::runtime_error("could not open socket");
    }
    m_connected = true;

    // first write trial
    try {
        send("data");
    } catch (...) {
        close();
        throw;
    }
}


} // namespace fgear
