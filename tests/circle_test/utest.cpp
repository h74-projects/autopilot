#include "mu_test.h"
#include <string>
#include "udp_server.hpp"
#include "udp_client.hpp"
#include "flight_gear.hpp"
#include <thread> // Include this for std::thread

using namespace std;
using namespace communication;

void udpCallback(const std::string& data, ssize_t size) {
    std::cout << "Received UDP data: " << data << " (Size: " << size << ")" << std::endl;
}

BEGIN_TEST(udp_communication_test)
    boost::asio::io_context io_context;
    FlightGear fg;

    // Start the UDP server
    int32_t serverPort = 5500; // Adjust the port if needed
    UDPServer udpServer(io_context, "127.0.0.1", serverPort);

    // Use a flag to indicate when the server has received data
    bool dataReceived = false;
    
    udpServer.start_listening([&](const std::string& data, ssize_t size) {
        udpCallback(data, size);
        dataReceived = true;
    });

    // Create and use the UDP client
    UDPClient udpClient(io_context, "127.0.0.1", serverPort);

    std::string receivedData;

    std::thread io_thread([&]() {
        io_context.run();
    });

    for (int i = 0; i < 5; ++i) {
        fg.take_off(); // Change flight status to "In Air"
        std::string testData = fg.get_flight_status();
        udpClient.send(testData);
        std::cout << "Flight status (take off): " << testData << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // Delay between sends

        fg.land(); // Change flight status to "Landed"
        testData = fg.get_flight_status();
        udpClient.send(testData);
        std::cout << "Flight status (land): " << testData << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // Delay between sends
    }

    io_context.stop();
    io_thread.join();

    ASSERT_THAT(dataReceived); 
   
END_TEST

TEST_SUITE(因果応報 [inga ōhō: bad causes bring bad results])

    TEST(udp_communication_test)

END_SUITE