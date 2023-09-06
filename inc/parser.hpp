#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>
#include <vector>
#include <iostream> 
#include <memory>

#include "lexer.hpp"
#include "ast_node.hpp"

namespace fg {
class Parser {
public:
    explicit Parser(std::string const& a_script_code);
    ~Parser() = default;
    std::vector<std::unique_ptr<ASTNode>> parse();

private:
    std::unique_ptr<ASTNode> parse_statement(std::vector<Token> const& a_tokens);
    std::unique_ptr<VariableNode> parse_variable(std::vector<Token> const& a_tokens);
    std::unique_ptr<PrintNode> parse_print(std::vector<Token> const& a_tokens);
    std::unique_ptr<SleepNode> parse_sleep(std::vector<Token> const& a_tokens);
    std::unique_ptr<WhileNode> parse_while(std::vector<Token> const& a_tokens);
    std::unique_ptr<BindNode> parse_bind(std::vector<Token> const& a_tokens);
    std::unique_ptr<IfNode> parse_if(std::vector<Token> const& a_tokens);
    std::unique_ptr<AssignmentNode> parse_assignment(std::vector<Token> const& a_tokens);
    std::unique_ptr<ArithmeticNode> parse_arithmetic(std::vector<Token> const& a_tokens);

    //std::string get_command_from_script();

private:   
    const std::string m_script_code;
    std::size_t m_pos;
    Lexer m_lexer;
};
} // namespace fg
#endif // PARSER_HPP
