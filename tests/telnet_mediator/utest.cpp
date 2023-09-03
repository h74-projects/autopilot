#include "mu_test.h"
#include "mediator_telnet.hpp"
#include "udp_server.hpp"
#include "my_udp.hpp"

#include <thread> // std::thread

using namespace fgear;

void udpCallback(const std::string& data, ssize_t size) {
    std::cout << "Received UDP data: " << data << " (Size: " << size << ")" << std::endl;
}

BEGIN_TEST(basic_test)
    int32_t server_port = 49002;
    TelnetMediator mediator{"generic_small.xml","127.0.0.1","127.0.0.1", 5401, server_port};
    mediator.set("/controls/switches/magnetos", 3);
    mediator.set("/controls/engines/current-engine/throttle", 0.2);
    mediator.set("/controls/engines/current-engine/mixture", 0.949);
    mediator.set("/controls/switches/master-bat", 1);
    mediator.set("/controls/switches/master-alt", 1);
    mediator.set("/controls/switches/master-avionics", 1);
    mediator.set("/sim/model/c172p/brake-parking", 0);
    mediator.set("/controls/engines/engine/primer", 3);
    mediator.set("/controls/switches/starter", 1);
    mediator.set("/engines/active-engine/auto-start", 1);
    std::cout << "\nengine rpm is: " << mediator.get("/engines/engine/rpm");
    mediator.set("/engines/engine/rpm", 800);
    
    ::usleep(250*1000);
    while (mediator.get("/engines/engine/rpm") < 750) {
        std::cout << "\nengine rpm is: " << mediator.get("/engines/engine/rpm");
        ::usleep(250*1000);
    }
    float h0 = mediator.get("/instrumentation/heading-indicator/offset-deg"); 
    mediator.set("/controls/flight/speedbrake", 0);
    ::sleep(10);
    mediator.set("/controls/engines/current-engine/throttle", 1);
    while (mediator.get("/instrumentation/altimeter/indicated-altitude-ft") < 1500) {
        mediator.set("flight_rudder", (h0 - mediator.get("/instrumentation/heading-indicator/offset-deg")) / 20);
        mediator.set("light_aileron", mediator.get("light_aileron") - (mediator.get("/instrumentation/attitude-indicator/indicated-roll-deg") / 70));
        mediator.set("flight_elevator", mediator.get("flight_elevator") - (mediator.get("/instrumentation/attitude-indicator/indicated-pitch-deg") / 50));
        std::cout << "\naltitude is: " << mediator.get("/instrumentation/altimeter/indicated-altitude-ft");
        ::usleep(250*1000);
    }


END_TEST

BEGIN_TEST(without_mediator)
    int32_t server_port = 49002;
    TelnetMediator mediator{"map_values.json","127.0.0.1","127.0.0.1", 5401, server_port};
    TelnetClient client{"127.0.0.1", 5401, 1000};
    client.send("set /controls/switches/magnetos 3\015\012");
    client.send("set /controls/engines/current-engine/throttle 0.2\015\012");
    client.send("set /controls/engines/current-engine/mixture 0.949\015\012");
    client.send("set /controls/switches/master-bat 1\015\012");
    client.send("set /controls/switches/master-alt 1\015\012");
    client.send("set /controls/switches/master-avionics 1\015\012");
    client.send("set /controls/switches/master-avionics 1\015\012");
    client.send("set /controls/switches/master-avionics 1\015\012");
    mediator.set("c172p_brake-parking", 0);
    mediator.set("engine_primer", 3);
    mediator.set("switches_starter", 1);
    mediator.set("active-engine_auto-start", 1);
    std::cout << "\nengine rpm is: " << mediator.get("engine_rpm");
    mediator.set("engine_rpm", 800);
    client.send("set /engines/engine/rpm 800\015\012");
    ::usleep(250*1000);
    while (mediator.get("engine_rpm") < 750) {
        std::cout << "\nengine rpm is: " << mediator.get("engine_rpm");
        ::usleep(250*1000);
    }
    float h0 = mediator.get("heading-indicator_offset-deg"); 
    mediator.set("flight_speedbrake", 0);
    ::sleep(10);
    mediator.set("/controls/engines/current-engine/throttle", 1);
    while (mediator.get("altimeter_indicated-altitude-ft") < 1500) {
        mediator.set("flight_rudder", (h0 - mediator.get("heading-indicator_offset-deg")) / 20);
        mediator.set("light_aileron", mediator.get("light_aileron") - (mediator.get("attitude-indicator_indicated-roll-deg") / 70));
        mediator.set("flight_elevator", mediator.get("flight_elevator") - (mediator.get("attitude-indicator_indicated-pitch-deg") / 50));
        std::cout << "\naltitude is: " << mediator.get("altimeter_indicated-altitude-ft");
        ::usleep(250*1000);
    }


END_TEST


BEGIN_TEST(server_test)
    int32_t server_port = 49002;
    TelnetMediator mediator{"map_values.json","127.0.0.1","127.0.0.1", 5401, server_port};

    while(true){}

END_TEST

BEGIN_TEST(client_test)
    TelnetClient client{"127.0.0.1", 5401, 1000};
    try {
        client.send("get /sim/aircraft");
        std::string sims = client.read();
        std::cout << '\n' << sims << '\n';
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



BEGIN_SUITE("tel it to the judge")
    TEST(basic_test)
    IGNORE_TEST(client_test)  
    IGNORE_TEST(server_test)

END_SUITE