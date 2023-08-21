#ifndef UDP_CLIENT_HPP
#define UDP_CLIENT_HPP

#include <boost/asio.hpp>
#include <functional>

class UDPClient {
public:
    UDPClient(boost::asio::io_context& io_context, const std::string& server_ip, int32_t server_port);
    ~UDPClient();

    void send(const std::string& data);
    void receive(std::function<void(const std::string&, ssize_t)> callback);

private:
    void do_receive();

    boost::asio::io_context& m_io_context;
    boost::asio::ip::udp::socket m_socket;
    boost::asio::ip::udp::endpoint m_server_endpoint;
    char m_recv_buffer[1024];
    std::function<void(const std::string&, ssize_t)> m_receive_callback;
};

#endif // UDP_CLIENT_HPP
