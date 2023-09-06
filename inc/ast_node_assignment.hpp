#ifndef AST_NODE_ASSIGNMENT_HPP
#define AST_NODE_ASSIGNMENT_HPP

#include "ast_node.hpp"

#include <string> //std string
#include <memory> // unique ptr

namespace fgear {

//TODO: will add to non bind map
class AssignmentNode : public ASTNode {
public:
    AssignmentNode(const std::string& a_identifier, float const& a_value);

    void visit(Interpretert& a_interpreter) override;

private:
    std::string m_identifier;
    float m_value;
};

} // namespace fgear

#endif // AST_NODE_ASSIGNMENT_HPP