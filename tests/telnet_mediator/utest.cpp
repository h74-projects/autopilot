#include "mu_test.h"
#include "mediator_telnet.hpp"
#include "udp_server.hpp"

#include <thread> // std::thread

using namespace fgear;

void udpCallback(const std::string& data, ssize_t size) {
    std::cout << "Received UDP data: " << data << " (Size: " << size << ")" << std::endl;
}

BEGIN_TEST(basic_test)
    int32_t server_port = 49002;
    TelnetMediator mediator{"127.0.0.1","127.0.0.1", 5401, server_port};
    mediator.set("engine_throttle", 1.0);
    std::thread listener{[&mediator]{mediator.get_updates();}};
    ::sleep(3);
    float throttle = mediator.get("engine_throttle");
    ASSERT_THAT(throttle == 1.0);
    listener.join();

END_TEST

BEGIN_TEST(client_test)
    TelnetClient client{"127.0.0.1", 5401, 1000};
    try {
        client.send("get /sim/aircraft");
        std::string sim = client.read();
        std::cout << '\n' << sim << '\n';
    } catch (...) {
        std::cout << "\nNothing to read\n";
    }
    client.send("set /controls/flight/aileron -1.0");
    sleep(1);
    client.send("set /controls/flight/aileron 100.0");
    sleep(1);
    client.send("set /controls/flight/aileron 1.0");
    sleep(1);
    client.send("set /controls/flight/aileron 45.0");
    sleep(1);
    client.send("set /controls/flight/aileron -1.0");
    sleep(1);
    client.send("set /controls/flight/aileron -100.0");
    sleep(1);
    client.send("set /controls/flight/aileron 1.0");
    sleep(1);
    client.send("get /sim/aircraft");

    ASSERT_PASS();

END_TEST


BEGIN_TEST(listening_to_fgear)
    boost::asio::io_context io_context;

    // Start the UDP server
    uint32_t server_port = 49002; // Adjust the port if needed
    communication::UDPServer udpServer(io_context, "127.0.0.1", server_port);

    // Use a flag to indicate when the server has received data
    bool dataReceived = false;
    
    udpServer.start_listening([&](const std::string& data, ssize_t size) {
        udpCallback(data, size);
        dataReceived = true;
    });

    std::thread io_thread([&]() {
        io_context.run();
    });    
    while (true) {
    }

    io_thread.join();    


END_TEST

BEGIN_SUITE("tel it to the judge")
    TEST(basic_test)
    IGNORE_TEST(client_test)
    IGNORE_TEST(listening_to_fgear)    

END_SUITE