#include <unistd.h>
#include <arpa/inet.h>
#include <iostream>

#include "udp_server.hpp"

namespace communication { 

UDPServer::UDPServer(std::string const& a_ip, int32_t a_port)
: m_socket(m_context, udp::endpoint(udp::v4(), a_port))
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
        do_receive();
        auto handler = [this]() {
            while (m_listening) {
                m_context.run();
            }
        };
        m_handler = std::thread{handler};
    }
}

void UDPServer::do_receive() 
{
    m_socket.async_receive_from(boost::asio::buffer(m_recv_buffer), m_sender_endpoint,
        [this](boost::system::error_code ec, std::size_t bytes_recvd) {
            if (!ec && bytes_recvd > 0) {
                m_callback(m_recv_buffer, bytes_recvd);
                do_receive(); 
            }
        });
}

void UDPServer::stop_listening()
{
    if (m_listening) {
        m_listening = false;
        m_socket.close();
        m_handler.join();
    }
}

} //namespace communication  