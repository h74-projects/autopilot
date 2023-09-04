#ifndef AST_NODE_CONDITION_HPP
#define AST_NODE_CONDITION_HPP

#include "ast_node.hpp"

#include <string> // std string
#include <vector> // vector
#include <memory> // unique ptr
#include <functional> // functional

namespace fgear {

class ConditionNode : public ASTNode {
public:
    //TODO: change members and ctor (the condition part)
    explicit ConditionNode(std::function<bool(std::vector<std::unique_ptr<ASTNode>> const&)> const& a_condition, std::vector<std::unique_ptr<ASTNode>>&& a_nodes);
    ~ConditionNode() = default;

    void operator()() override;

    bool condition();

private:
    //TODO: think if we really need a const & here
    std::function<bool(std::vector<std::unique_ptr<ASTNode>> const&)> m_condition;
    //TODO: think if we need unique ptr or shared
    std::vector<std::unique_ptr<ASTNode>> m_nodes;
};


} // namespace fgear

#endif // AST_NODE_CONDITION_HPP