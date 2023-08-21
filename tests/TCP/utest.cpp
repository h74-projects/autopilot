#include "mu_test.h"
#include <string>
#include "tcp_client.hpp"
#include "tcp_server.hpp"

using namespace std;

void tcpCallback(const std::string& data, ssize_t size) {
    std::cout << "Received TCP data: " << data << " (Size: " << size << ")" << std::endl;
}

BEGIN_TEST(tcp_communication_test)
    boost::asio::io_context io_context;

    // Start the TCP server
    int32_t serverPort = 12345; // Adjust the port if needed
    TCPServer tcpServer(io_context, serverPort);
    std::string receivedData;

    std::mutex dataMutex; // For thread-safe data access

    tcpServer.start_accepting([&](boost::asio::ip::tcp::socket acceptedSocket) {
        boost::asio::streambuf buffer;
        boost::asio::read_until(acceptedSocket, buffer, '\n');
        std::istream is(&buffer);
        std::lock_guard<std::mutex> lock(dataMutex);
        std::getline(is, receivedData);
        acceptedSocket.close();
        io_context.stop(); // Stop the io_context after receiving data
    });

    // Create and use the TCP client
    TCPClient tcpClient(io_context, "127.0.0.1", serverPort);

    std::string testData = "Hello, TCP Server!";
    std::string sentData;

    tcpClient.connect();
    tcpClient.send(testData);
    tcpClient.receive([&](const std::string& data, ssize_t size) {
        std::lock_guard<std::mutex> lock(dataMutex);
        sentData = data;
        size = size;
    });

    io_context.run(); // Run the event loop to handle async operations

    ASSERT_EQUAL(sentData, testData);
    ASSERT_EQUAL(receivedData, testData);
END_TEST

TEST_SUITE(因果応報 [inga ōhō: bad causes bring bad results])

    TEST(tcp_communication_test)

END_SUITE
