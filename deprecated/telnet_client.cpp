#include "telnet_client.hpp"

#include <string.h> // memset
#include <netinet/in.h> // sockaddr_in
#include <sys/socket.h> // socket
#include <unistd.h>// close
#include <arpa/inet.h> //inet_pton
#include <fcntl.h> // fcntl 

#include <exception> // exception
#include <stdexcept> // std exceptions

namespace fgear {

constexpr uint32_t BUFFER_SIZE = 4096;

namespace {

// bool unblock_socket(int32_t const& a_socket)
// {
//     int flags = fcntl(a_socket,F_GETFL);
//     if(flags  == -1)
//     {
//         return false;
//     }
//     if((fcntl(a_socket,F_SETFL,flags | O_NONBLOCK)) == -1)
//     {
//         return false;
//     }
//     return true;    
// }  

bool connect_to_telnet(int32_t const& a_socket, std::string const& a_address, uint32_t a_port)
{
    struct sockaddr_in serv_addr;
    memset(&serv_addr,0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(a_port);
    if (inet_pton(AF_INET, a_address.c_str(), &serv_addr.sin_addr) <= 0) {
        return false;
    }

    if (connect(a_socket, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        return false;
    }

    return true;    
}

} // namespace

TelnetClient::TelnetClient(std::string const& a_address, uint32_t const& a_port, uint32_t const& a_time_out)
: m_socket(-1)
, m_timeout(a_time_out)
{
    m_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (m_socket < 0) {
        throw std::runtime_error("could not open socket");
    }
    // if (not unblock_socket(m_socket)) {
    //     throw std::runtime_error("could not unblock socket");
    // }
    set_timeout(m_timeout);

    if (not connect_to_telnet(m_socket, a_address, a_port)) {
        close(m_socket);
        throw std::runtime_error("could not connect to telnet");
    }

    // first write trial
    if (send("data") < 4) {
        close(m_socket);
        throw std::runtime_error("could not connect to telnet");
    }
}

TelnetClient::~TelnetClient()
{
    close(m_socket);
}


ssize_t TelnetClient::send(std::string const& a_msg)
{
    return ::write(m_socket, a_msg.c_str(), a_msg.size());
}


std::string TelnetClient::read() 
{
    char buffer[BUFFER_SIZE];
    ssize_t len = ::read(m_socket, buffer, BUFFER_SIZE - 1);
    if (len < 0) {
        throw std::runtime_error("can't read");
    }
    else if (len > 0) {
        std::string result{buffer,static_cast<size_t>(len)};
        size_t last_valid = result.find_last_not_of("\r\n");
        if (last_valid != std::string::npos) {
            result.erase(last_valid + 1);
        }
        return result;
    }
    throw std::runtime_error("can't read");
    
}

void TelnetClient::set_timeout(uint32_t const& a_time)
{
    m_timeout = a_time;

    struct timeval read_timeout;
    read_timeout.tv_sec = 0; 
    read_timeout.tv_usec = a_time * 1000;
    setsockopt(m_socket, SOL_SOCKET, SO_RCVTIMEO, &read_timeout, sizeof(read_timeout));

    struct timeval write_timeout;
    write_timeout.tv_sec = 0; 
    write_timeout.tv_usec = a_time * 1000;
    setsockopt(m_socket, SOL_SOCKET, SO_SNDTIMEO, &write_timeout, sizeof(write_timeout));

}


} // namespace fgear
