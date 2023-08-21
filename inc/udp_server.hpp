#ifndef UDP_HPP
#define UDP_HPP

#include <functional>

class UDPServer {
public:
    UDPServer(std::string a_ip, uint32_t a_port);
    ~UDPServer();

    bool initialize_server();
    void start_listening(std::function<void(std::string, ssize_t)> a_callback);
    void stop_listening();

private:
    std::string m_ip;
    uint32_t m_port;
    uint32_t m_sockfd;
    bool m_listening;
};

#endif // UDP_HPP
