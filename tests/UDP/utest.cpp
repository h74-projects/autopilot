#include "mu_test.h"
#include <string>
#include "udp_server.hpp"

using namespace std;


void udpCallback(const std::string& data, ssize_t size) 
{
    std::cout << "Received UDP data: " << data << " (Size: " << size << ")" << std::endl;
}

BEGIN_TEST(udp_test)
    boost::asio::io_context io_context;

    UDPServer udpServer(io_context, "127.0.0.1", 5500);

    udpServer.start_listening(udpCallback);

    udpServer.stop_listening();

    ASSERT_PASS();
	
END_TEST

TEST_SUITE(因果応報 [inga ōhō: bad causes bring bad results])

    TEST(udp_test)

END_SUITE