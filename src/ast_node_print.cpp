#include "ast_node_print.hpp"
#include "interpreter.hpp"

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

void PrintNode::visit(Interpreter& a_interpreter)
{
    std::cout << m_text;
    a_interpreter.nothing();
}

} // namespace fgear
