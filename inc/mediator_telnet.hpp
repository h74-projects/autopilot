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
#include "udp_server.hpp"

#include <memory> // shared ptr
#include <cstdint> // int32_t
#include <mutex> // mutex
#include <tuple> // tuple
#include <nlohmann/json.hpp> // nlhomann::json::iterator
#include <thread> // listener thread

namespace fgear {

class TelnetMediator : public Mediator {
public:
    TelnetMediator(std::string const & a_server_ip, std::string const & a_telnet_ip, uint32_t const& a_telnet_port, int32_t const& a_udp_port);
    ~TelnetMediator();

    void set(std::string const& a_key ,float const& a_var) override;

    float get(std::string const& a_key) override;

    void get_updates();

private:
    std::string make_command(std::string const& a_key ,float const& a_var, std::string const& a_command);
    void fill_map(std::string const& a_filename);
    void update_map(std::string const& a_message, ssize_t a_len);
    
private:
    //TODO: instead of string key we need some variable type enum
    //key: name of property as written under the name tag in the json
    //value: tupple of string of the property as written in node at the property tree and a Var value
    concurrency::BlockingMap<std::string, std::tuple<std::string, float>> m_variables;
    //TODO: in the future abstract Client class
    std::mutex m_mtx;
    boost::asio::io_context m_context;
    communication::UDPServer m_server;
    TelnetClient m_telnet;
    bool m_active;
    std::vector<std::thread> m_listener;
};

} // namespace fgear

#endif // MEDIATOR_TELNET_HPP