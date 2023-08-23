#include "mu_test.h"
#include "mediator_telnet.hpp"

using namespace fgear;

BEGIN_TEST(basic_test)
    try {
        TelnetMediator mediator{"127.0.0.1", 5401};
        mediator.set("alieron", -1.0);
        sleep(1);
        mediator.set("alieron", 1.0);
        sleep(1);
        mediator.set("rudder", 1.0);
        sleep(1);
        mediator.set("rudder", -1.0);
    } catch (...) {
        ASSERT_FAIL("\nYou fucked up\n");
    }
    ASSERT_PASS();

END_TEST


BEGIN_SUITE("tel it to the judge")
    TEST(basic_test)

END_SUITE