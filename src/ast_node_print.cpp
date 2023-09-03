#include "ast_node_print.hpp"

#include <iostream> // cout

namespace fgear {

PrintNode::PrintNode(const std::string& text)
: m_text(text)
{
}

std::string PrintNode::text() const
{
    return m_text;
}

void PrintNode::operator()()
{
    std::cout << m_text;
}

} // namespace fgear
