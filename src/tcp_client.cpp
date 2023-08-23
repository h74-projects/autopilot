#include "tcp_client.hpp"

TCPClient::TCPClient(boost::asio::io_context& io_context, std::string const& server_ip, int32_t server_port)
: m_io_context(io_context)
, m_socket(io_context)
, m_server_endpoint(boost::asio::ip::address::from_string(server_ip), server_port)
{
}

TCPClient::~TCPClient()
{
    close();
}

void TCPClient::connect() 
{
    m_socket.connect(m_server_endpoint);
}

void TCPClient::send(const std::string& data) 
{
    boost::asio::write(m_socket, boost::asio::buffer(data));
}

void TCPClient::receive(std::function<void(const std::string&, ssize_t)> callback) 
{
    m_receive_callback = std::move(callback);
    do_receive();
}

void TCPClient::do_receive() 
{
    m_socket.async_receive(boost::asio::buffer(m_recv_buffer),
        [this](boost::system::error_code ec, std::size_t bytes_received) {
            if (!ec && bytes_received > 0) {
                m_receive_callback(m_recv_buffer, bytes_received);
                do_receive(); // continue listening for more data
            }
        });
}

void TCPClient::close() 
{
    if (m_socket.is_open()) {
        m_socket.close();
    }
}
