#include "mu_test.h"
#include "pugixml.hpp"
#include "SystemAnalyser.hpp"

#include <stdio.h>
#include <fstream>
#include <iostream>

BEGIN_TEST(xml_logic)
    pugi::xml_document doc;
    auto declaration = doc.append_child(pugi::node_declaration);
    declaration.append_attribute("version") = "1.0";

    auto property_root = doc.append_child("PropertyList");
    auto generic_root = property_root.append_child("generic");
    auto output_root = generic_root.append_child("output");
    auto separator = output_root.append_child("line_separator");

    separator.append_child(pugi::node_pcdata).set_value("newline");
    auto var_separator = output_root.append_child("var_separator");
    var_separator.append_child(pugi::node_pcdata).set_value(",");

    std::string file_name = "test_file.xml"; 
    doc.save_file(file_name.c_str());   
    
    pugi::xml_document loaded_doc;
    ASSERT_THAT(loaded_doc.load_file(file_name.c_str()));

END_TEST

BEGIN_TEST(xml_node_logic)
    pugi::xml_document doc;
    std::string file_name = "test_file.xml"; 
    if (not doc.load_file(file_name.c_str())) {
        ASSERT_FAIL("nope");
    }
    pugi::xml_node root = doc.child("PropertyList").child("generic").child("output");
    pugi::xml_node node = root.append_child("chunk");
    auto name = node.append_child("name");
    auto type = node.append_child("type");
    auto format =  node.append_child("format");
    auto property = node.append_child("node");

    std::string node_name = "trial";
    std::string node_property = "property";
    name.append_child(pugi::node_pcdata).set_value(node_name.c_str());
    type.append_child(pugi::node_pcdata).set_value("float");
    property.append_child(pugi::node_pcdata).set_value(node_property.c_str());

    std::string chunk_format = node_property + ":%f";
    format.append_child(pugi::node_pcdata).set_value(chunk_format.c_str());
    std::string new_file{"new_file.xml"};
    doc.save_file(new_file.c_str());

    pugi::xml_document second_doc;
    ASSERT_THAT(second_doc.load_file(new_file.c_str()));
    ASSERT_THAT(second_doc.child("PropertyList").child("generic").child("output").child("chunk").child("name").value() == node_name.c_str());


END_TEST

BEGIN_TEST(SystemAnalyser_test)
    util::SystemAnalyser analyser{};
    analyser.RunCommand("sudo cp new_file.xml /usr/share/games/flightgear/Protocol/new_file.xml");
    analyser.RunCommand("sudo rm /usr/share/games/flightgear/Protocol/new_file.xml");
    ASSERT_PASS();
END_TEST

BEGIN_SUITE("no lo entiendo")
    TEST(xml_logic)
    TEST(xml_node_logic)
    TEST(SystemAnalyser_test)


END_SUITE