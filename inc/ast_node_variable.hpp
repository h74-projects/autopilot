#ifndef AST_NODE_VARIABLE_HPP
#define AST_NODE_VARIABLE_HPP

#include "ast_node.hpp"

namespace fgear {

class VariableNode : public ASTNode {
public:
    VariableNode(std::string const& a_name, std::string const& a_property);

    std::string name() const;
    std::string property() const;

    void operator()() override;

private:
    std::string m_name;
    std::string m_property;
};

} // namespace fgear

#endif // AST_NODE_VARIABLE_HPP