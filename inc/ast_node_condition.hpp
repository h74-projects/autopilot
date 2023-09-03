#ifndef AST_NODE_CONDITION_HPP
#define AST_NODE_CONDITION_HPP

#include "ast_node.hpp"

#include <string> // std string

namespace fgear {

class ConditionNode : public ASTNode {
public:
    explicit ConditionNode(std::string const& a_id, std::string const& a_num, std::string const& a_symbol);
    ~ConditionNode() = default;

    void operator()() override;

    bool condition();

private:
    std::string m_condition;
    std::string m_number; 
    std::string m_idtfr; 

};


} // namespace fgear

#endif // AST_NODE_CONDITION_HPP