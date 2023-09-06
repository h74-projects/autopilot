#include "interpreter.hpp"

namespace fgear {



Interpreter::Interpreter()
{
    create_xml();
}

void Interpreter::create_xml()
{
    auto declaration = m_doc.append_child(pugi::node_declaration);
    declaration.append_attribute("version") = "1.0";

    auto property_root = m_doc.append_child("PropertyList");
    auto generic_root = property_root.append_child("generic");
    auto output_root = generic_root.append_child("output");
    auto separator = output_root.append_child("line_separator");

    separator.append_child(pugi::node_pcdata).set_value("newline");
    auto var_separator = output_root.append_child("var_separator");
    var_separator.append_child(pugi::node_pcdata).set_value(",");
}

} // namespace fgear
