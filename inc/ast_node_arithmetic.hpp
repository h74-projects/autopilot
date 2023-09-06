#ifndef AST_NODE_ARITHMETIC_HPP
#define AST_NODE_ARITHMETIC_HPP

#include "ast_node.hpp"
#include "arithmetics.hpp"

#include <string> // std string
#include <memory> // unique ptr

namespace fgear {

//TODO: will do operator on left and right
class ArithmeticNode : public ASTNode {
public:
    //TODO: maybe make the op a shared pointer and use the freight thingy design pattern
    ArithmeticNode(std::unique_ptr<ASTNode>&& a_left, std::unique_ptr<Arithmetics>&& a_op, std::unique_ptr<ASTNode>&& a_right);

    void operator()() override;

    void visit(Interpreter const& a_interpreter) override;

    std::shared_ptr<ASTNode> result();

private:
    std::unique_ptr<Arithmetics> m_op;
    std::unique_ptr<ASTNode> m_left;
    std::unique_ptr<ASTNode> m_right;
    std::shared_ptr<ASTNode> m_result;
};

} // namespace fgear

#endif // AST_NODE_ARITHMETIC_HPP