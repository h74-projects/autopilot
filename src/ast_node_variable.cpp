#include "ast_node_variable.hpp"
#include "interpreter.hpp"

namespace fgear {

VariableNode::VariableNode(std::string const& a_name, std::string const& a_property)
: m_property{a_property}
, m_name{a_name}
{
}

std::string VariableNode::name() const 
{
    return m_name;
}

std::string VariableNode::property() const
{
    return m_property;
}

void VariableNode::visit(Interpreter& a_interpreter)
{
    a_interpreter.m_environment.get()->insert(m_name, std::stof(m_property));
}

} // namespace fgear
