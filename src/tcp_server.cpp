#include "tcp_server.hpp"

TCPServer::TCPServer(boost::asio::io_context& io_context, int32_t port)
    : m_io_context(io_context),
      m_acceptor(io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)),
      m_socket(io_context) {}

TCPServer::~TCPServer() {
    stop_accepting();
}

void TCPServer::start_accepting(std::function<void(boost::asio::ip::tcp::socket)> accept_callback) {
    m_accept_callback = std::move(accept_callback);
    do_accept();
}

void TCPServer::do_accept() {
    m_acceptor.async_accept(m_socket, [this](boost::system::error_code ec) {
        if (!ec) {
            m_accept_callback(std::move(m_socket));
            do_accept(); // Continue accepting connections
        }
    });
}

void TCPServer::stop_accepting() {
    if (m_acceptor.is_open()) {
        m_acceptor.close();
    }
}