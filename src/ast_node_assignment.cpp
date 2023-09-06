#include "ast_node_assignment.hpp"

namespace fgear {

AssignmentNode::AssignmentNode(const std::string& a_identifier, float const& a_value)
: m_identifier{a_identifier}
, m_value{a_value}
{
}

void AssignmentNode::visit(Interpreter& a_interpreter)
{
    a_interpreter.m_environment.get()->set(m_identifier, m_value);
}

} // namespace fgear
