#include "ast_node_while.hpp"

namespace fgear {

WhileNode::WhileNode(std::unique_ptr<ConditionNode> a_cond, std::vector<std::unique_ptr<ASTNode>> a_body)
: m_condition{std::move(a_cond)}
, m_loop_body{std::move(a_body)}
{
}

void WhileNode::visit(Interpreter& a_interpreter)
{
    while (m_condition.get()->condition()) {
        for (auto& it : m_loop_body) {
            it.get()->visit();
        }
    }
}

} // namespace fgear
