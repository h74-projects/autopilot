#include "ast_node_condition.hpp"
#include "interpreter.hpp"

namespace fgear {

ConditionNode::ConditionNode(std::function<bool(std::vector<std::unique_ptr<ASTNode>> const&)> const& a_condition, std::vector<std::unique_ptr<ASTNode>>&& a_nodes)
: m_condition{a_condition}
, m_nodes{std::move(a_nodes)}
{
}

bool ConditionNode::condition()
{
    return m_condition(m_nodes);
}

} // namespace fgear
