#include "ast_node_sleep.hpp"

namespace fgear {

SleepNode::SleepNode(std::string const& a_time)
: m_time(a_time) 
{ 
}


int SleepNode::time() const
{
    return std::stoi(m_time);
}

void SleepNode::visit(Interpreter& a_interpreter)
{
    ::usleep(std::stoi(m_time));
}

} // namespace fgear
