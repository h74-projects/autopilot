#include "ast_node_variable.hpp"

namespace fgear {

VariableNode::VariableNode(std::string const& a_name, std::string const& a_property)
: m_name(a_name)
, m_property(a_property) 
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


} // namespace fgear
