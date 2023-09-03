#ifndef TELNET_CLIENT_HPP
#define TELNET_CLIENT_HPP

#include <string> // std::string
#include <cstdint> // uint32_t

namespace fgear {

class TelnetClient {

public:
    TelnetClient(std::string const& a_address, uint32_t const& a_port, uint32_t const& a_time_out);
    ~TelnetClient();

    ssize_t send(std::string const& a_msg);
    std::string read();

    //in milliseconds
    void set_timeout(uint32_t const& a_time); 

private:    
    int32_t m_socket;
    uint32_t m_timeout;
};

} // namespace fgear

#endif // TELNET_CLIENT_HPP