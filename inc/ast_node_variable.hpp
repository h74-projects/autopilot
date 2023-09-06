#ifndef AST_NODE_VARIABLE_HPP
#define AST_NODE_VARIABLE_HPP

#include "ast_node.hpp"
#include "variables_environment.hpp"

#include <string> // std string

namespace fgear {

class VariableNode : public ASTNode {
public:
    explicit VariableNode(std::string const& a_name, std::string const& a_property);
    ~VariableNode() = default;

    std::string name() const;
    std::string property() const;

    void visit(Interpreter& a_interpreter) override;

private:
    std::string m_property;
    std::string m_name;
};

} // namespace fgear

#endif // AST_NODE_VARIABLE_HPP