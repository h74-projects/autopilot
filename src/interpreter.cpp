#include "interpreter.hpp"

namespace fgear {

Interpreter::Interpreter(std::string const& a_file_name, std::unique_ptr<Environment>&& a_environment)
: m_parser{a_file_name}
, m_environment{std::move(a_environment)}
{
    create_xml();
    m_program = m_parser.parse();
    m_analyser.RunCommand("sudo rm /usr/share/games/flightgear/Protocol/generic_small.xml");
    bind_all();
    m_variables = std::make_shared<Variables>();
    m_variables.get()->load_file(m_doc);
    m_environment.get()->load_binded(m_variables);
}

std::shared_ptr<Variables> Interpreter::get_binded()
{
    return m_variables;
}


void Interpreter::accept(std::unique_ptr<ASTNode> const& a_node)
{
    a_node.get()->visit(*this);
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

void Interpreter::bind_all()
{
    auto begin = m_program.begin();
    auto end = m_program.end();
    while (begin != end) {
        //TODO: remove all bind nodes from vector!
        auto node = dynamic_cast<BindNode*>(begin->get());
        if (not (node == nullptr)) {
            accept(*begin);
        }
        ++begin;
    }
    m_doc.save_file("generic_small.xml");
    send_generic_protocol();
}

void Interpreter::send_generic_protocol()
{
    m_analyser.RunCommand("sudo cp generic_small.xml /usr/share/games/flightgear/Protocol/generic_small.xml");
}

void Interpreter::run()
{
    auto begin = m_program.begin();
    auto end = m_program.end();
    while (begin != end) {
        auto node = dynamic_cast<BindNode*>(begin->get());
        if (node == nullptr) {
            accept(*begin);
        }
        ++begin;
    }    
}

} // namespace fgear
