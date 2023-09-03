#ifndef AST_NODE_BIND_HPP
#define AST_NODE_BIND_HPP

#include "ast_node.hpp"

namespace fgear {

class BindNode : public ASTNode {
public:
    BindNode(std::string const& a_name, std::string const& a_property);

    std::string name() const;
    std::string property() const;

    void operator()() override;

private:
    std::string m_name;
    std::string m_property;
};

} // namespace fgear

#endif // AST_NODE_BIND_HPP