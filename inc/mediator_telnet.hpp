#ifndef MEDIATOR_TELNET_HPP
#define MEDIATOR_TELNET_HPP

//style guide:
// int = "int"
// double = "double"
// float = "float"
// bool = "bool"
// int32_t = "int32_t"


#include "mediator.hpp"
#include "blocking_map.hpp"
#include "var.hpp"
#include "tcp_client.hpp"
#include "udp_server.hpp"

#include <memory> // shared ptr
#include <cstdint> // int32_t
#include <mutex> // mutex
#include <tuple> // tuple

namespace fgear {

class TelnetMediator : public Mediator {
public:
    TelnetMediator(boost::asio::io_context& io_context, const std::string& server_ip, int32_t server_port);
    ~TelnetMediator();

    void set(std::string const& a_key ,Var const& a_var) override;

    Var get(std::string const& a_key) override;

private:
    std::string make_set_command(std::string const& a_key ,Var const& a_var);

private:
    //TODO: instead of string key we need some variable type enum
    //tuple order <property, typename, Var>
    concurrency::BlockingMap<std::string, std::tuple<std::string, std::string, Var>> m_variables;
    //TODO: in the future abstract Client class
    TCPClient m_client;
    std::mutex m_mtx;    
};

} // namespace fgear

#endif // MEDIATOR_TELNET_HPP