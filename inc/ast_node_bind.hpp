#ifndef AST_NODE_BIND_HPP
#define AST_NODE_BIND_HPP

#include "ast_node.hpp"
#include "variables_environment.hpp"

#include <string> // std string

namespace fgear {

class BindNode : public ASTNode {
public:
    //TODO: add a filename member maybe
    explicit BindNode(std::string const& a_name, std::string const& a_property);
    ~BindNode() = default;

    std::string name() const;
    std::string property() const;

    void visit(Interpreter& a_interpreter) override;

private:
    std::string m_name;
    std::string m_property;
};

} // namespace fgear

#endif // AST_NODE_BIND_HPP