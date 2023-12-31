#ifndef UDP_HPP
#define UDP_HPP

#include <boost/asio.hpp>
#include <boost/system/error_code.hpp>
#include <functional>
#include <thread> // thread

namespace communication { 

using boost::asio::ip::udp;

class UDPServer {
public:
    UDPServer(boost::asio::io_context& a_context, std::string const& a_ip, int32_t a_port);
    ~UDPServer();

    void start_listening(std::function<void(std::string const&, ssize_t)> a_callback);
    void stop_listening();

private:
    void do_receive();

private:
    boost::asio::io_context& m_context;
    udp::socket m_socket;
    udp::endpoint m_sender_endpoint;
    char m_recv_buffer[4096];
    std::function<void(std::string const&, ssize_t)> m_callback;
    bool m_listening;
    std::string m_ip;
    std::thread m_runner;
};

} //namespace communication 

#endif // UDP_HPP
