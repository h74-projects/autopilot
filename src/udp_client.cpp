#include "udp_client.hpp"

UDPClient::UDPClient(boost::asio::io_context& io_context, const std::string& server_ip, int32_t server_port)
    : m_io_context(io_context),
      m_socket(io_context, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), 0)),
      m_server_endpoint(boost::asio::ip::address::from_string(server_ip), server_port) {}

UDPClient::~UDPClient() {}

void UDPClient::send(const std::string& data) {
    m_socket.send_to(boost::asio::buffer(data), m_server_endpoint);
}

void UDPClient::receive(std::function<void(const std::string&, ssize_t)> callback) {
    m_receive_callback = std::move(callback);
    do_receive();
}

void UDPClient::do_receive() {
    m_socket.async_receive_from(boost::asio::buffer(m_recv_buffer), m_server_endpoint,
        [this](boost::system::error_code ec, std::size_t bytes_received) {
            if (!ec && bytes_received > 0) {
                m_receive_callback(m_recv_buffer, bytes_received);
                do_receive(); // Continue listening for more data
            }
        });
}