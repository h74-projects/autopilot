#ifndef AST_NODE_VARIABLE_HPP
#define AST_NODE_VARIABLE_HPP

#include "ast_node.hpp"

#include <string> // std string

namespace fgear {

class VariableNode : public ASTNode {
public:
    explicit VariableNode(std::string const& a_name, std::string const& a_property);
    ~VariableNode() = default;

    std::string name() const;
    std::string property() const;

    //TODO: make to number through member
    void operator()() override;

private:
    std::string m_name;
    std::string m_property;
};

} // namespace fgear

#endif // AST_NODE_VARIABLE_HPP