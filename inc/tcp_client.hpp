#ifndef TCP_CLIENT_HPP
#define TCP_CLIENT_HPP

#include <boost/asio.hpp>
#include <functional>
#include <iostream>

namespace fgear {



class TCPClient {
public:
    TCPClient(boost::asio::io_context& a_io_context, const std::string& a_server_ip, int32_t a_server_port);
    ~TCPClient();

    void connect();
    void send(const std::string& data);
    void receive(std::function<void(const std::string&, ssize_t)> callback);
    void close();

private:
    void do_receive();

    boost::asio::io_context& m_io_context;
    boost::asio::ip::tcp::socket m_socket;
    boost::asio::ip::tcp::endpoint m_server_endpoint;
    char m_recv_buffer[1024];
    std::function<void(const std::string&, ssize_t)> m_receive_callback;
};

} // namespace fgear

#endif // TCP_CLIENT_HPP