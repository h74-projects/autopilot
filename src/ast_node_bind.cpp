#include "ast_node_bind.hpp"
#include "pugixml.hpp" // xml_nodes

namespace fgear {

BindNode::BindNode(std::string const& a_name, std::string const& a_property)
: m_name(a_name)
, m_property(a_property) 
{
}

void BindNode::visit(Interpreter& a_interpreter)
{
    pugi::xml_node root = a_interpreter.m_doc.child("PropertyList").child("generic").child("output");
    pugi::xml_node node = root.append_child("chunk");
    auto name = node.append_child("name");
    auto type = node.append_child("type");
    auto format =  node.append_child("format");
    auto property = node.append_child("node");

    name.append_child(pugi::node_pcdata).set_value(m_name.c_str());
    type.append_child(pugi::node_pcdata).set_value("float");
    property.append_child(pugi::node_pcdata).set_value(m_property.c_str());

    std::string chunk_format = m_property + ":%f";
    format.append_child(pugi::node_pcdata).set_value(chunk_format.c_str());
}

std::string BindNode::name() const 
{
    return m_name;
}

std::string BindNode::property() const
{
    return m_property;
}

//TODO: check how to add to xml file

} // namespace fgear
