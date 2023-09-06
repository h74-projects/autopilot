#include "interpreter.hpp"

namespace fgear {



Interpreter::Interpreter(std::string const& a_file_name, std::unique_ptr<Environment>&& a_environment)
: m_parser{a_file_name}
, m_environment{std::move(a_environment)}
{
    create_xml();
    m_program = m_parser.parse();
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
