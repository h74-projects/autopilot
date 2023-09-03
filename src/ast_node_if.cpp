#include "ast_node_if.hpp"

namespace fgear {

IfNode::IfNode(std::unique_ptr<ASTNode>&& a_cond, std::vector<std::unique_ptr<ASTNode>>&& a_if_body, std::vector<std::unique_ptr<ASTNode>>&& a_else_body)
: m_condition{std::move(a_cond)}
, m_if_body{std::move(a_if_body)}
, m_else_body{std::move(a_else_body)}
{
}

void IfNode::operator()()
{
    //TODO: if???? 
                    {
        for (size_t i = 0; i < m_if_body.size(); ++i) {
            m_if_body.at(i).get()->operator()();
        } 
    } else {
        for (size_t i = 0; i < m_else_body.size(); ++i) {
            m_else_body.at(i).get()->operator()();
        }
    }
}



} // namespace fgear
