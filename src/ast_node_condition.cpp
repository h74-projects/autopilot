#include "ast_node_condition.hpp"

namespace fgear {

ConditionNode::ConditionNode(std::string const& a_id , std::string const& a_num , std::string const& a_symbol)
: m_condition(a_symbol)
, m_number(a_num)
, m_idtfr(a_id)
{
}

} // namespace fgear
