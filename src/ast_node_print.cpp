#include "ast_node_print.hpp"

namespace fgear {

PrintNode::PrintNode(const std::string& text)
: m_text(text)
{
}

std::string PrintNode::text() const
{
    return m_text;
}

} // namespace fgear
