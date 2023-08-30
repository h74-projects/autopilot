#include "mu_test.h"
#include "telemetry.hpp"
#include "mediator_telnet.hpp"
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
    std::shared_ptr<Variables> variables;
    fill_map("generic_small.xml", *variables);
    std::shared_ptr<Protocol> protocol{std::make_shared<Protocol>(variables)};
    TelnetClient client{"127.0.0.1", 5401, 500};
    Telemetry telemetry{protocol, std::make_unique<UdpServer>(49002)};
    client.send("set /controls/switches/magnetos 3\015\012");
    ::sleep(1);
    float magnetos = variables.get()->get("/controls/switches/magnetos");
    std::cout << "\nmagnetos is: " << magnetos << '\n';
    ASSERT_THAT(std::abs(magnetos - 3) >= 0.00000001f);

END_TEST

BEGIN_SUITE("tel me why")
    TEST(basic_test)

END_SUITE
