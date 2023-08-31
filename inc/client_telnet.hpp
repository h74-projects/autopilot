#ifndef CLIENT_TELNET_HPP
#define CLIENT_TELNET_HPP

#include "client.hpp"

#include "Poco/Net/DialogSocket.h" // dialog socket

namespace fgear {

constexpr size_t BUFFER_SIZE = 4096;

class TelnetClient : public Client {
public:
    TelnetClient();
    ~TelnetClient();

    TelnetClient(TelnetClient const&) = delete;
    TelnetClient& operator=(TelnetClient const&) = delete;

    TelnetClient(TelnetClient&&) = delete;
    TelnetClient& operator=(TelnetClient&&) = delete;

    void connect(std::string const& a_address, uint16_t a_port) override;
    bool send(std::string const& a_message) override;

    std::string recieve() override;    

private:
    Poco::Net::DialogSocket m_socket;
    char m_buffer[BUFFER_SIZE];
    bool m_connected;

};

} // namespace fgear

#endif // CLIENT_TELNET_HPP