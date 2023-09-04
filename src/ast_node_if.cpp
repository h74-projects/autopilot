#include "ast_node_if.hpp"

namespace fgear {

IfNode::IfNode(std::unique_ptr<ConditionNode>&& a_cond, std::vector<std::unique_ptr<ASTNode>>&& a_if_body, std::vector<std::unique_ptr<ASTNode>>&& a_else_body)
: m_condition{std::move(a_cond)}
, m_if_body{std::move(a_if_body)}
, m_else_body{std::move(a_else_body)}
{
}

void IfNode::operator()()
{
    if (m_condition.get()->condition()) {
        for (auto& it : m_if_body) {
            it.get()->operator()();
        }   
    } else {
        for (auto& it : m_else_body) {
            it.get()->operator()();
        }
    }
}



} // namespace fgear
