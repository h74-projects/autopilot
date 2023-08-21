#include "mu_test.h"
#include <string>
#include "udp_server.hpp"

using namespace std;

// Define a callback function for UDP data handling in tests
void udpCallback(const std::string& data, ssize_t size) {
    // Do something with the received UDP data (for testing purposes)
    std::cout << "Received UDP data: " << data << " (Size: " << size << ")" << std::endl;
}

BEGIN_TEST(udp_test)
    // Create an io_context for Boost.Asio
    boost::asio::io_context io_context;

    // Create the UDPServer object
    UDPServer udpServer(io_context, "127.0.0.1", 5500);

    // Initialize the server

    // Start listening with the provided callback function
    udpServer.start_listening(udpCallback);

    // Simulate receiving UDP data (for testing purposes)
    // You can use tools like netcat to send UDP packets or use actual clients

    // Stop listening
    udpServer.stop_listening();
    ASSERT_PASS();
END_TEST

TEST_SUITE(因果応報 [inga ōhō: bad causes bring bad results])

    TEST(udp_test)

END_SUITE