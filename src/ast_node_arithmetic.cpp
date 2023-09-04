#include "ast_node_arithmetic.hpp"

namespace fgear {

ArithmeticNode::ArithmeticNode(std::unique_ptr<ASTNode>&& a_left, std::unique_ptr<Arithmetics>&& a_op, std::unique_ptr<ASTNode>&& a_right)
: m_op{std::move(a_op)}
, m_left{std::move(a_left)}
, m_right{std::move(a_right)}
, m_result{nullptr}
{
}

void ArithmeticNode::operator()()
{
    m_result = m_op.get()->op(m_left, m_right);
}

std::shared_ptr<ASTNode> ArithmeticNode::result()
{
    if (m_result.get() == nullptr) {
        m_result = m_op.get()->op(m_left, m_right);
    }
    return m_result;
}

} // namespace fgear

