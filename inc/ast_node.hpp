#ifndef AST_NODE_HPP
#define AST_NODE_HPP

#include <memory> //unique ptrs


namespace fgear {

class Interpreter;

class ASTNode {
public:
    virtual ~ASTNode() = default;

    virtual void visit(Interpreter& a_interpreter) = 0;

protected:
    ASTNode() = default;
    ASTNode(ASTNode const&) = default;
    ASTNode(ASTNode&&) = default;
    ASTNode& operator=(ASTNode const&) = default;
    ASTNode& operator=(ASTNode&&) = default;
};

} // namespace fgear

#endif // AST_NODE_HPP