#include "ast_node_bind.hpp"

namespace fgear {

BindNode::BindNode(std::string const& a_name, std::string const& a_property)
: m_name(a_name)
, m_property(a_property) 
{
}

std::string BindNode::name() const 
{
    return m_name;
}

std::string BindNode::property() const
{
    return m_property;
}


} // namespace fgear
