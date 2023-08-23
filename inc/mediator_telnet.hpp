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
#include "telnet_client.hpp"

#include <memory> // shared ptr
#include <cstdint> // int32_t
#include <mutex> // mutex
#include <tuple> // tuple

namespace fgear {

class TelnetMediator : public Mediator {
public:
    TelnetMediator(std::string const & a_server_ip, uint32_t const& a_server_port);
    ~TelnetMediator() = default;

    void set(std::string const& a_key ,Var const& a_var) override;

    //Var get(std::string const& a_key) override;

private:
    std::string make_command(std::string const& a_key ,Var const& a_var, std::string const& a_command);

private:
    //TODO: instead of string key we need some variable type enum
    //tuple order <property, typename, Var>
    concurrency::BlockingMap<std::string, std::tuple<std::string, std::string, Var>> m_variables;
    TelnetClient m_telnet;
    //TODO: in the future abstract Client class
    std::mutex m_mtx;    
};

} // namespace fgear

#endif // MEDIATOR_TELNET_HPP