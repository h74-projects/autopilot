#ifndef AST_NODE_SLEEP_HPP
#define AST_NODE_SLEEP_HPP

#include "ast_node.hpp"

#include <string> // std string

namespace fgear {

class SleepNode : public ASTNode {
public:
    SleepNode(std::string const& a_time);

    int time() const
    {
        return std::stoi(m_time);
    }

    void visit(Interpreter& a_interpreter) override;

private:
    std::string m_time;
};


} // namespace fgear

#endif // AST_NODE_SLEEP_HPP