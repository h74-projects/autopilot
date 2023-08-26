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

//TODO: load map from file
TelnetMediator::TelnetMediator(std::string const & a_server_ip, std::string const & a_telnet_ip, uint32_t const& a_telnet_port, int32_t const& a_udp_port)
: m_server{m_context, a_server_ip, a_udp_port}
, m_telnet{a_telnet_ip, a_telnet_port,TIME_OUT}
, m_active{true}
{
    fill_map("../../files/map_values.json");
    m_listener.push_back(std::thread{[this]{get_updates();}});
    m_listener.push_back(std::thread{[this]() {
        while(m_active) {
            m_context.run();
        }
    }});

}

TelnetMediator::~TelnetMediator()
{
    m_active = false;
    for (auto& thread : m_listener) {
        thread.join();
    }
}

void TelnetMediator::set(std::string const& a_key ,float const& a_var)
{
    std::string set_command = make_command(a_key, a_var, "set");
    std::unique_lock lock{m_mtx};
    m_telnet.send(set_command);
}

float TelnetMediator::get(std::string const& a_key)
{
    return std::get<1>(m_variables.at(a_key));
}

std::string TelnetMediator::make_command(std::string const& a_key ,float const& a_var, std::string const& a_command)
{
    std::string return_command = a_command + ' ' + std::get<0>(m_variables.at(a_key)) + ' ' + std::to_string(a_var) + "\015\012";
    return return_command;  
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
        m_variables[begin.value()["name"]] = std::make_tuple(begin.value()["node"], float{});
        ++begin;
    }
}

void TelnetMediator::get_updates()
{
    auto lambda = [this](const std::string& data, ssize_t size) {
            update_map(data, size);
            std::cout << data;
    };
    m_server.start_listening(lambda);
    while(m_active) {}
}

void TelnetMediator::update_map(std::string const& a_message, ssize_t a_len)
{
    size_t name_index{};
    size_t value_index = a_message.find(":") + 1;
    size_t end_index = a_message.find(",");
    while (end_index <= a_message.size()) {
        std::string name = a_message.substr(name_index, value_index - 1 - name_index);
        float value = std::stof(a_message.substr(value_index, end_index - value_index));
        float& curr = std::get<1>(m_variables.at(name));
        if ( value != curr) {
            curr = value;
        }
        name_index = end_index + 1;
        value_index = a_message.find(":", name_index) + 1;
        end_index = a_message.find(",", name_index);
        name.clear();
    }
    ++a_len;

}

} // namespace fgear
