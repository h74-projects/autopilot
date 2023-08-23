#include "mediator_telnet.hpp"

#include <variant> //std::get

constexpr uint32_t TIME_OUT = 30;

namespace fgear {

//TODO: load map from file
TelnetMediator::TelnetMediator(std::string const& a_server_ip, uint32_t const& a_server_port)
: m_telnet{a_server_ip, a_server_port,TIME_OUT}
{
    m_variables["alieron"] = {"/controls/flight/aileron", "double", 0.0};
    m_variables["rudder"] = {"/controls/flight/rudder", "double", 0.0};
}

void TelnetMediator::set(std::string const& a_key ,Var const& a_var)
{
    std::unique_lock lock{m_mtx};
    std::string set_command = make_command(a_key, a_var, "set");
    m_telnet.send(set_command);
}

std::string TelnetMediator::make_command(std::string const& a_key ,Var const& a_var, std::string const& a_command)
{
    std::tuple value = m_variables.at(a_key);
    std::string return_command = a_command + ' ' + std::get<0>(value) + ' ';  
    if(std::get<1>(value) == "int") {
        return return_command += std::to_string(static_cast<int>(a_var));
    }

    if(std::get<1>(value) == "double") {
        return return_command += std::to_string(static_cast<double>(a_var));
    }

    if(std::get<1>(value) == "float") {
        return return_command += std::to_string(static_cast<float>(a_var));
    }

    if(std::get<1>(value) == "bool") {
        return return_command += std::to_string(static_cast<bool>(a_var));
    }

    throw std::invalid_argument("invalid argument");


}


} // namespace fgear
