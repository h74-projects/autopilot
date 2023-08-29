#include "mediator_telnet.hpp"
#include "pugixml.hpp"

#include <variant> //std::get
#include <iostream> // string stream
#include <fstream> // fstream
#include <algorithm> // remove if
#include <boost/algorithm/string.hpp> // erase all

//TODO: exception handling

constexpr uint32_t TIME_OUT = 500;

namespace fgear {

namespace {

} // namespace

TelnetMediator::TelnetMediator(std::string const & a_file_name, std::string const & a_server_ip, std::string const & a_telnet_ip, uint32_t const& a_telnet_port, int32_t const& a_udp_port)
: m_server{m_context,a_server_ip, a_udp_port}
, m_telnet{a_telnet_ip, a_telnet_port,TIME_OUT}
, m_active{true}
{
    fill_map(a_file_name);
    get_updates();
}

TelnetMediator::~TelnetMediator()
{
    m_active = false;
    m_server.stop_listening();
    // m_listener.join();

}

void TelnetMediator::set(std::string const& a_key ,float const& a_var)
{
    std::string set_command = make_command(a_key, a_var, "set");
    std::unique_lock lock{m_mtx};
    m_telnet.send(set_command);
}

float TelnetMediator::get(std::string const& a_key)
{
    return m_variables.at(a_key).load();
}

std::string TelnetMediator::make_command(std::string const& a_key ,float const& a_var, std::string const& a_command)
{
    std::string return_command = a_command + ' ' + a_key + ' ' + std::to_string(a_var) + "\015\012";
    return return_command;  
}

void TelnetMediator::fill_map(std::string const& a_filename)
{
    pugi::xml_document doc;
    if (!doc.load_file(a_filename.c_str())) {
        throw std::runtime_error("failed to load");
    }
    
    for (pugi::xpath_node chunk_node : doc.select_nodes("/PropertyList/generic/output/chunk")) {
        pugi::xml_node node = chunk_node.node();
        std::string node_path = node.child_value("node");

        if (!node_path.empty()) {
            m_variables[node_path].store(float{});
        }
    }
}

void TelnetMediator::get_updates()
{
    auto lambda = [this](const std::string& data, ssize_t size) {
            // std::unique_lock lock{m_mtx};
            std::cout << "\ncheck\n";
            update_map(data, size);
    };
    m_server.start_listening(lambda);
    m_listener.push_back(std::thread{[this]{m_context.run();}});
}

void TelnetMediator::update_map(std::string const& a_message, ssize_t a_len)
{
    size_t name_index{};
    size_t value_index = a_message.find(":") + 1;
    size_t end_index = a_message.find(",");
    while (value_index <= a_message.size()) {
        std::string name = a_message.substr(name_index, value_index - 1 - name_index);
        float value = std::stof(a_message.substr(value_index, end_index - value_index));
        if (m_variables.at(name).load() != value) {
            m_variables.at(name).store(value);
        }
        name_index = end_index + 1;
        value_index = a_message.find(":", name_index) + 1;
        end_index = a_message.find(",", name_index);
        name.clear();
    }
    ++a_len;

}

} // namespace fgear
