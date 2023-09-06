#ifndef AST_NODE_PRINT_HPP
#define AST_NODE_PRINT_HPP

#include "ast_node.hpp"

#include <string> // std string

namespace fgear {

class PrintNode : public ASTNode {
public:
    explicit PrintNode(const std::string& text);
    ~PrintNode() = default;

    std::string text() const;

    //TODO: prints to console
    void operator()() override;

private:
    std::string m_text;
};

} // namespace fgear

#endif // AST_NODE_PRINT_HPP