#ifndef TCP_SERVER_HPP
#define TCP_SERVER_HPP

#include <boost/asio.hpp>
#include <functional>

class TCPServer {
public:
    TCPServer(boost::asio::io_context& io_context, int32_t port);
    ~TCPServer();

    void start_accepting(std::function<void(boost::asio::ip::tcp::socket)> accept_callback);
    void stop_accepting();

private:
    void do_accept();

    boost::asio::io_context& m_io_context;
    boost::asio::ip::tcp::acceptor m_acceptor;
    boost::asio::ip::tcp::socket m_socket;
    std::function<void(boost::asio::ip::tcp::socket)> m_accept_callback;
    bool m_accepting;
};

#endif // TCP_SERVER_HPP
