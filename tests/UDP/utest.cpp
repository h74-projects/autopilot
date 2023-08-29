#include "mu_test.h"
#include <string>
#include "mu_test.h"
#include <string>
#include "udp_server.hpp"
#include "udp_client.hpp"
#include <thread> // Include this for std::thread

using namespace std;
using namespace communication;

void udpCallback(const std::string& data, ssize_t size) {
    std::cout << "Received UDP data: " << data << " (Size: " << size << ")" << std::endl;
}

BEGIN_TEST(udp_communication_test)
    boost::asio::io_context io_context;

    // Start the UDP server
    int32_t serverPort = 5500; // Adjust the port if needed
    UDPServer udpServer(io_context,"127.0.0.1", serverPort);

    // Use a flag to indicate when the server has received data
    bool dataReceived = false;
    
    udpServer.start_listening([&](const std::string& data, ssize_t size) {
        udpCallback(data, size);
        dataReceived = true;
    });

    // Create and use the UDP client
    fgear::UDPClient udpClient(io_context, "127.0.0.1", serverPort);

    std::string testData = "Hello, UDP Server!";
    std::string receivedData;

    for (int i = 0; i < 5; ++i) {
        udpClient.send(testData);
    }

    // Create a thread to run the io_context event loop
    std::thread io_thread([&]() {
        io_context.run();
    });

    io_thread.join(); // Wait for the io_thread to finish

    // Wait for a short period to ensure that the server has received data
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    ASSERT_THAT(dataReceived); // Ensure that the server has received data
    // You might want to add additional assertions here

END_TEST

TEST_SUITE(因果応報 [inga ōhō: bad causes bring bad results])
    TEST(udp_communication_test)

END_SUITE