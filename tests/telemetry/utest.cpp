#include "mu_test.h"
#include "telemetry.hpp"
#include "middle_man.hpp"
#include "client_telnet.hpp"
#include "server_udp.hpp"
#include "pugixml.hpp" // for xml file

#include <cmath> // abs

void fill_map(std::string const& a_filename, fgear::Variables& a_variables)
{
    pugi::xml_document doc;
    if (!doc.load_file(a_filename.c_str())) {
        throw std::runtime_error("failed to load");
    }
    
    for (pugi::xpath_node chunk_node : doc.select_nodes("/PropertyList/generic/output/chunk")) {
        pugi::xml_node node = chunk_node.node();
        std::string node_path = node.child_value("node");

        if (!node_path.empty()) {
            a_variables.insert(node_path ,float{});
        }
    }
}


BEGIN_TEST(basic_test)
    using namespace fgear;
    std::shared_ptr<Variables> variables = std::make_shared<Variables>();
    fill_map("generic_small.xml", *variables);
    std::shared_ptr<Protocol> protocol{std::make_shared<Protocol>(variables)};
    TelnetClient client;
    client.connect("127.0.0.1", 5401);
    Telemetry telemetry{protocol, std::make_unique<UdpServer>(49002), "127.0.0.1"};
    telemetry.run_telemetry();
    client.send("set /controls/engines/current-engine/mixture 0.949");
    ::sleep(2);
    float mixture = variables.get()->get("/controls/engines/current-engine/mixture");
    std::cout << "\nmixture is: " << mixture << '\n';
    ASSERT_THAT(std::abs(mixture - 0.949) < 0.00000001f);

END_TEST

BEGIN_TEST(server_test)
    using namespace fgear;
    std::shared_ptr<Variables> variables = std::make_shared<Variables>();
    fill_map("generic_small.xml", *variables);
    std::shared_ptr<Protocol> protocol{std::make_shared<Protocol>(variables)};
    UdpServer server{49002};
    server.connect();
    server.start_listening(protocol);
    ::sleep(30);
    float mixture = variables.get()->get("/controls/engines/current-engine/mixture");
    std::cout << "\nmixture is: " << mixture << '\n';
    ASSERT_THAT(std::abs(mixture - 0.949) < 0.00000001f);    


END_TEST


BEGIN_TEST(middle_man_test)
    using namespace fgear;
    std::shared_ptr<Variables> variables = std::make_shared<Variables>();
    fill_map("generic_small.xml", *variables);
    std::shared_ptr<Protocol> protocol{std::make_shared<Protocol>(variables)};
    MiddleMan middleman(std::make_unique<TelnetClient>(), 5401);
    Telemetry telemetry{protocol, std::make_unique<UdpServer>(49002), "127.0.0.1"};
    telemetry.run_telemetry();
    middleman.send_message("set /controls/engines/current-engine/throttle 0.2");
    middleman.send_message("set /controls/flight/rudder 1");
    middleman.send_message("set /controls/flight/aileron 1");
    middleman.send_message("set /controls/switches/magnetos 3");
    middleman.send_message("set /controls/engines/current-engine/mixture 0.949");
    ::sleep(3);
    float throttle = variables.get()->get("/controls/engines/current-engine/throttle");
    float rudder = variables.get()->get("/controls/flight/rudder");
    float aileron = variables.get()->get("/controls/flight/aileron");
    float magnetos = variables.get()->get("/controls/switches/magnetos");
    float mixture = variables.get()->get("/controls/engines/current-engine/mixture");
    ASSERT_THAT(std::abs(throttle - 0.2) < 0.00000001f);   
    ASSERT_THAT(std::abs(rudder - 1) < 0.00000001f);   
    ASSERT_THAT(std::abs(aileron - 1) < 0.00000001f);   
    ASSERT_THAT(std::abs(magnetos - 3) < 0.00000001f);   
    ASSERT_THAT(std::abs(mixture - 0.949) < 0.00000001f);   


END_TEST

BEGIN_SUITE("tel me why")
    IGNORE_TEST(basic_test)
    IGNORE_TEST(server_test)
    TEST(middle_man_test)

END_SUITE
