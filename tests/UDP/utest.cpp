#include "mu_test.h"
#include <string>
#include "udp_server.hpp"
#include "udp_client.hpp"

using namespace std;

void udpCallback(const std::string& data, ssize_t size) {
    std::cout << "Received UDP data: " << data << " (Size: " << size << ")" << std::endl;
}

BEGIN_TEST(udp_communication_test)
    boost::asio::io_context io_context;

    // Start the UDP server
    int32_t serverPort = 5500; // Adjust the port if needed
    UDPServer udpServer(io_context, "127.0.0.1", serverPort);

    udpServer.start_listening(udpCallback);

    // Create and use the UDP client
    UDPClient udpClient(io_context, "127.0.0.1", serverPort);

    std::string testData = "Hello, UDP Server!";
    std::string receivedData;

    for (int i = 0; i < 5; ++i) {
        udpClient.send(testData);
    }

    udpClient.receive([&](const std::string& data, ssize_t size) {
        receivedData = data;
        size = size;
    });

    io_context.run(); // Run the event loop to handle async operations

    ASSERT_EQUAL(receivedData, testData);
END_TEST

TEST_SUITE(因果応報 [inga ōhō: bad causes bring bad results])

    TEST(udp_communication_test)

END_SUITE