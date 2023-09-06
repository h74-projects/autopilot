#ifndef AST_NODE_WHILE_HPP
#define AST_NODE_WHILE_HPP

#include "ast_node.hpp"
#include "ast_node_condition.hpp"

#include <vector> // vector
#include <memory> // unique ptr

namespace fgear {

class WhileNode : public ASTNode {
public:
    WhileNode(std::unique_ptr<ConditionNode> a_cond, std::vector<std::unique_ptr<ASTNode>> a_body);

    void visit(Interpreter& a_interpreter) override;
private:
    std::unique_ptr<ConditionNode> m_condition;
    std::vector<std::unique_ptr<ASTNode>> m_loop_body;
};

} // namespace fgear

#endif 