#ifndef AST_NODE_BIND_HPP
#define AST_NODE_BIND_HPP

#include "ast_node.hpp"

#include <string> // std string

namespace fgear {

class BindNode : public ASTNode {
public:
    //TODO: add a filename member maybe
    explicit BindNode(std::string const& a_name, std::string const& a_property);

    std::string name() const;
    std::string property() const;

    //TODO: will write to xml file
    void operator()() override;

private:
    std::string m_name;
    std::string m_property;
};

} // namespace fgear

#endif // AST_NODE_BIND_HPP