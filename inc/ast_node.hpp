#ifndef AST_NODE_HPP
#define AST_NODE_HPP

#include "interpreter.hpp"

#include <memory> //unique ptrs

namespace fgear {

class ASTNode {
public:
    virtual ~ASTNode() = default;

    //TODO: think if we want a return value
    virtual void operator()() = 0;

    virtual void visit(Interpreter const& a_interpreter) = 0;

protected:
    ASTNode() = default;
    ASTNode(ASTNode const&) = default;
    ASTNode(ASTNode&&) = default;
    ASTNode& operator=(ASTNode const&) = default;
    ASTNode& operator=(ASTNode&&) = default;
};

} // namespace fgear

#endif // AST_NODE_HPP