#ifndef TELNET_CLIENT_HPP
#define TELNET_CLIENT_HPP

#include <string> // std::string
#include <cstdint> // uint32_t

namespace fgear {

class TelnetClient {

public:
    TelnetClient(std::string const& a_address, uint32_t const& a_port, uint32_t const& a_time_out);
    ~TelnetClient();

    int32_t send(std::string const& a_msg);
    std::string read(void);

    //in milliseconds
    void set_timeout(uint32_t const& a_time);

private:
    int close(void);

private:    
    int32_t m_socket;
    //TODO: check if this member is necessary
    uint32_t m_timeout;
    bool m_is_shutdown;
    bool m_connected;
};

} // namespace fgear

#endif // TELNET_CLIENT_HPP