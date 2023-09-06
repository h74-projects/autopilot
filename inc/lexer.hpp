// Lexer.hpp
#ifndef LEXER_HPP
#define LEXER_HPP

#include <string>
#include <vector>
#include <boost/tokenizer.hpp>

enum class TokenType {
    VAR,
    BIND,
    IF,
    ELSE,
    WHILE,
    IDENTIFIER,
    NUMBER,
    STRING_LITERAL,
    ASSIGNMENT,
    CONNECT,
    TELEMETRY,
    PLUS,
    MINUS,
    ASTERISK,
    SLASH,
    OPEN_PAREN,
    CLOSE_PAREN,
    OPEN_SCOP,
    CLOSE_SCOP,
    COLON,
    COMMA,
    SEMICOLON,
    SLEEP,
    PRINT,
    SYMBOL,
    GREATER_EQUAL,
    GREATER,
    LESS_EQUAL,
    LESS,
    NOT_EQUAL
};

// Token structure
struct Token {
    TokenType m_type;
    std::string m_value;
};

class Lexer {
public:
    Lexer() = default;
    std::vector<Token> tokenize(std::string const& a_code) const;
};

#endif // LEXER_HPP
