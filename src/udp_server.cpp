#include <unistd.h>
#include <arpa/inet.h>
#include <iostream>

#include "udp_server.hpp"

UDPServer::UDPServer(std::string a_ip, uint32_t a_port)
: m_ip(std::move(a_ip))
, m_port(a_port)
, m_sockfd(-1)
, m_listening(false) 
{
}

UDPServer::~UDPServer() 
{
    stop_listening();
}

bool UDPServer::initialize_server() 
{
    if ((m_sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        return false;
    }

    sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(m_port);

    if (bind(m_sockfd, reinterpret_cast<struct sockaddr*>(&server_addr), sizeof(server_addr)) < 0) {
        perror("Binding failed");
        return false;
    }
    return true;
}

void UDPServer::start_listening(std::function<void(std::string, ssize_t)> a_callback) 
{
    if (!m_listening) {
        m_listening = true;

        while (m_listening) {
            sockaddr_in client_addr{};
            socklen_t client_len = sizeof(client_addr);
            char buffer[1024];

            ssize_t data_size = recvfrom(m_sockfd, buffer, sizeof(buffer), 0,
                                         reinterpret_cast<struct sockaddr*>(&client_addr), &client_len);

            if (data_size >= 0) {
                buffer[data_size] = '\0';
                a_callback(buffer, data_size);
            }
        }
    }
}

void UDPServer::stop_listening() {
    if (m_listening) {
        m_listening = false;
        close(m_sockfd);
    }
}

