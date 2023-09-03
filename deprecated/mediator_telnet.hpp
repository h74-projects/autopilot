#ifndef MEDIATOR_TELNET_HPP
#define MEDIATOR_TELNET_HPP

#include "mediator.hpp"
#include "blocking_map.hpp"
#include "var.hpp"
#include "telnet_client.hpp"
#include "udp_server.hpp"

#include <memory> // shared ptr
#include <cstdint> // int32_t
#include <mutex> // mutex
#include <tuple> // tuple
#include <thread> // listener thread
#include <atomic> // atomic float

// xml chunk:
// 	<chunk>
    // 	<node>/property/name</node>
    // 	<name>property_name</name> -> as will be sent from the simulator
	// 	<type>float</type>
	// 	<format>property_name:%f</format>
	// </chunk>

//json node:
//    "/property/node/name/": {
    // 	"node": "/property/node/name/",
    // 	"name": "property_node_name",
	// 	"type": "float",
	// 	"format": "%f"
    // },

namespace fgear {

class TelnetMediator : public Mediator {
public:
    TelnetMediator(std::string const & a_file_name, std::string const & a_address, std::string const & a_telnet_ip, uint32_t const& a_telnet_port, int32_t const& a_udp_port);
    ~TelnetMediator();

    void set(std::string const& a_key ,float const& a_var) override;

    float get(std::string const& a_key) override;


private:
    void get_updates();
    std::string make_command(std::string const& a_key ,float const& a_var, std::string const& a_command);
    void fill_map(std::string const& a_filename);
    void update_map(std::string const& a_message, ssize_t a_len);
    
private:
    concurrency::BlockingMap<std::string, std::atomic<float>> m_variables;
    //TODO: in the future abstract Client class
    mutable std::mutex m_mtx;
    boost::asio::io_context m_context;
    communication::UDPServer m_server;
    TelnetClient m_telnet;
    std::vector<std::thread> m_listener;
    bool m_active;
};

} // namespace fgear

#endif // MEDIATOR_TELNET_HPP