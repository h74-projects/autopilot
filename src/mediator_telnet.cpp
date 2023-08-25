#include "mediator_telnet.hpp"
#include "pugixml.hpp"

#include <variant> //std::get
#include <iostream> // string stream
#include <fstream> // fstream


constexpr uint32_t TIME_OUT = 500;

namespace fgear {

namespace {

bool compare_vars(nlohmann::json::iterator const& a_iterator, std::tuple<std::string, Var> const& a_value)
{
    Var value = std::get<1>(a_value);
    if(value.type_id() == std::any{int{}}.type().name()) {
        return a_iterator.value() == static_cast<int>(std::get<1>(a_value));
    }

    if(value.type_id() == std::any{double{}}.type().name()) {
        return a_iterator.value() == static_cast<double>(std::get<1>(a_value));
    }

    if(value.type_id() == std::any{float{}}.type().name()) {
        return a_iterator.value() == static_cast<float>(std::get<1>(a_value));
    }

    if(value.type_id() == std::any{bool{}}.type().name()) {
        return a_iterator.value() == static_cast<bool>(std::get<1>(a_value));
    }
    throw std::invalid_argument("invalid comparison");    
}

} // namespace

//TODO: load map from file
TelnetMediator::TelnetMediator(std::string const & a_server_ip, std::string const & a_telnet_ip, uint32_t const& a_telnet_port, int32_t const& a_udp_port)
: m_server{m_context, a_server_ip, a_udp_port}
, m_telnet{a_telnet_ip, a_telnet_port,TIME_OUT}
, m_active{true}
{
    fill_map("../../files/map_values.json");
}

TelnetMediator::~TelnetMediator()
{
    m_active = false;
    m_server.stop_listening();
}

void TelnetMediator::set(std::string const& a_key ,Var const& a_var)
{
    std::string set_command = make_command(a_key, a_var, "set");
    std::unique_lock lock{m_mtx};
    m_telnet.send(set_command);
}

Var TelnetMediator::get(std::string const& a_key)
{
    return std::get<1>(m_variables.at(a_key));
}

std::string TelnetMediator::make_command(std::string const& a_key ,Var const& a_var, std::string const& a_command)
{
    Var value = std::get<1>(m_variables.at(a_key));
    std::string return_command = a_command + ' ' + std::get<0>(m_variables.at(a_key)) + ' ';  
    if(value.type_id() == std::any{int{}}.type().name()) {
        return return_command += std::to_string(static_cast<int>(a_var)) + "\015\012";
    }

    if(value.type_id() == std::any{double{}}.type().name()) {
        return return_command += std::to_string(static_cast<double>(a_var)) + "\015\012";
    }

    if(value.type_id() == std::any{float{}}.type().name()) {
        return return_command += std::to_string(static_cast<float>(a_var)) + "\015\012";
    }

    if(value.type_id() == std::any{bool{}}.type().name()) {
        return return_command += std::to_string(static_cast<bool>(a_var)) + "\015\012";
    }

    throw std::invalid_argument("invalid argument");
}

void TelnetMediator::fill_map(std::string const& a_filename)
{
    std::fstream file(a_filename);
    if (not file.is_open()) {
        throw std::runtime_error("could not open file");
    }

    nlohmann::json data = nlohmann::json::parse(file);
    auto begin = data.begin();
    auto end = data.end();
    while (begin != end) {
        m_variables[begin.value()["name"]] = std::make_tuple(begin.value()["node"], Var(begin.value()["format"]));
        ++begin;
    }
}

// should be run in a different thread (or inifinte loop will follow)
void TelnetMediator::get_updates()
{
    while (m_active) {
        m_server.start_listening([&, this](const std::string& data, ssize_t size) {
            update_map(data, size);
        });
    }
}

void TelnetMediator::update_map(std::string const& a_message, ssize_t a_len)
{
    nlohmann::json json_parse{nlohmann::json::parse(a_message)};
    auto begin = json_parse.begin();
    auto end = json_parse.end();
    while (begin != end) {
        if (not compare_vars(begin, m_variables.at(begin.key()))) {
            insert_to_map(begin);
        }
        ++begin;
    }
    ++a_len; 
}

void TelnetMediator::insert_to_map(nlohmann::json::iterator const& a_iterator)
{
    //TODO: add an operator for json iterator
    std::get<1>(m_variables.at(a_iterator.key())) = (a_iterator.value());
}

} // namespace fgear
