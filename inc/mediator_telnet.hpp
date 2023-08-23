#ifndef MEDIATOR_TELNET_HPP
#define MEDIATOR_TELNET_HPP

#include "mediator.hpp"
#include "blocking_map.hpp"
#include "var.hpp"
#include "udp_client.hpp"

#include <memory> // shared ptr
#include <cstdint> // int32_t

namespace fgear {

class TelnetMediator : public Mediator {
public:
    TelnetMediator(boost::asio::io_context& io_context, const std::string& server_ip, int32_t server_port);

    void set(std::string const& a_key ,Var const& a_var) override;

    Var get(std::string const& a_key) override;

private:
    concurrency::BlockingMap<std::string, Var> m_variables;
    concurrency::BlockingMap<std::string, Var> m_calculations;
    //TODO: in the future abstract Client class
    UDPClient m_client;
};

} // namespace fgear

#endif // MEDIATOR_TELNET_HPP