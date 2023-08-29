#include <unistd.h>
#include <arpa/inet.h>
#include <iostream>

#include "udp_server.hpp"

namespace communication { 

UDPServer::UDPServer(boost::asio::io_context& a_context,std::string const& a_ip, int32_t a_port)
: m_context(a_context)
, m_socket(a_context, udp::endpoint(udp::v4(), a_port))
, m_listening(false) 
, m_ip(a_ip)
{
}

UDPServer::~UDPServer() 
{
    stop_listening();
}

void UDPServer::start_listening(std::function<void(const std::string&, ssize_t)> a_callback) 
{
    if (!m_listening) {
        m_listening = true;
        m_callback = a_callback;
        m_runner = std::thread{[this]{do_receive();}};
    }
}

void UDPServer::do_receive() 
{
    m_socket.async_receive_from(boost::asio::buffer(m_recv_buffer), m_sender_endpoint,
        [this](boost::system::error_code ec, std::size_t bytes_recvd) {
            if (!ec && bytes_recvd > 0) {
                m_callback(m_recv_buffer, bytes_recvd);
            }
            throw boost::system::system_error(ec);
    });
    m_context.run();
}

void UDPServer::stop_listening()
{
    if (m_listening) {
        m_listening = false;
        m_context.stop();
        m_runner.join();
        m_socket.close();
    }
}

} //namespace communication  