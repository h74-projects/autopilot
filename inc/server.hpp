#ifndef SERVER_HPP
#define SERVER_HPP

#include "protocol.hpp"

#include <memory> // shared ptr
#include <cstdint> // uint32_t

namespace fgear {

class Server {
public:
    virtual ~Server() = default;

    virtual void connect(std::string const& a_address) = 0;

    virtual void start_listening() = 0;

protected:
    Server(std::shared_ptr<Protocol> a_protocol, uint32_t const& a_port) : m_protocol{a_protocol}, m_port{a_port}{};
    Server(Server const&) = default;
    Server& operator=(Server const&) = default;

private:
    std::shared_ptr<Protocol> m_protocol;
    uint32_t m_port;
};

} // namespace fgear

#endif // SERVER_HPP