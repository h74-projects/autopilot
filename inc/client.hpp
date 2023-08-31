#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string> // std::string
#include <cstdint> // uint16_t

namespace fgear {

class Client {
public:
    virtual ~Client() = default;

    virtual void connect(std::string const& a_address, uint16_t a_port) = 0; 
    virtual bool send(std::string const& a_message) = 0;

    virtual std::string recieve() = 0;

protected:
    Client() = default;
    Client(Client const&) = default;
    Client& operator=(Client const&) = default;

};

} // namespace fgear

#endif // CLIENT_HPP