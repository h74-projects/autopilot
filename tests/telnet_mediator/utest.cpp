#include "mu_test.h"
#include "mediator_telnet.hpp"

using namespace fgear;

BEGIN_TEST(basic_test)
    // try {
        TelnetMediator mediator{"127.0.0.1", 5401};
        mediator.set("aileron", -1.0);
        mediator.set("aileron", 1.0);
        mediator.set("rudder", 1.0);
        mediator.set("rudder", -1.0);
    // } catch (...) {
    //     ASSERT_FAIL("\nYou fucked up\n");
    // }
    ASSERT_PASS();

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


BEGIN_SUITE("tel it to the judge")
    TEST(basic_test)
    TEST(client_test)

END_SUITE