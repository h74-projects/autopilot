#include "lexer.hpp"

namespace {

TokenType get_token_type(std::string const& token_str) 
{
    // keywords
    switch (token_str[0]) {
        case 'v':
            if (token_str == "var") return TokenType::VAR;
            break;
        case 'b':
            if (token_str == "bind") return TokenType::BIND;
            break;
        case 'i':
            if (token_str == "if") return TokenType::IF;
            break;
        case 'e':
            if (token_str == "else") return TokenType::ELSE;
            break;
        case 'w':
            if (token_str == "while") return TokenType::WHILE;
            break;
        case 'p':
            if (token_str == "print") return TokenType::PRINT;
            break;
        case 's':
            if (token_str == "sleep") return TokenType::SLEEP;
            break;
        case 'c':
            if (token_str == "connect") return TokenType::CONNECT;
            break;
        case 't':
            if (token_str == "telemetry") return TokenType::TELEMETRY;
            break;

    }

    // symbols
    switch (token_str[0]) {
        case '=':
            return TokenType::ASSIGNMENT;
        case '+':
            return TokenType::PLUS;
        case '-':
            return TokenType::MINUS;
        case '*':
            return TokenType::ASTERISK;
        case '/':
            return TokenType::SLASH;
        case '(':
            return TokenType::OPEN_PAREN;
        case ')':
            return TokenType::CLOSE_PAREN;
        case '{':
            return TokenType::OPEN_SCOP;
        case '}':
            return TokenType::CLOSE_SCOP;
        case ':':
            return TokenType::COLON;
        case ',':
            return TokenType::COMMA;
        case ';':
            return TokenType::SEMICOLON;
        case '>':
            if (token_str == ">=") return TokenType::GREATER_EQUAL;
            return TokenType::GREATER;
        case '<':
            if (token_str == "<=") return TokenType::LESS_EQUAL;
            return TokenType::LESS;
        case '!':
        if (token_str == "!=") return TokenType::NOT_EQUAL;
        break;
}

    // identifier 
    if (std::isalpha(token_str[0]) || token_str[0] == '_') {
        bool is_identifier = true;
        for (char c : token_str.substr(1)) {
            if (!std::isalnum(c) && c != '_') {
                is_identifier = false;
                break;
            }
        }
        if (is_identifier) return TokenType::IDENTIFIER;
    }

    // number 
    bool is_number = true;
    bool has_decimal_point = false;
    for (char c : token_str) {
    if (!std::isdigit(c)) {
        if (c == '.' && !has_decimal_point) {
            has_decimal_point = true;
        } else {
            is_number = false;
            break;
          }
        }
    }
    if (is_number) return TokenType::NUMBER;

    // string literal 
    if ((token_str.size() >= 2 && token_str.front() == '"' && token_str.back() == '"') ||
        (token_str.size() >= 2 && token_str.front() == '\'' && token_str.back() == '\'')) {
        return TokenType::STRING_LITERAL;
    }

    return TokenType::IDENTIFIER;
}
}

std::vector<Token> Lexer::tokenize(std::string const& sourceCode) const {
    std::vector<Token> tokens;

    boost::char_separator<char> separator(" \t\r\n");
    boost::tokenizer<boost::char_separator<char>> tokenizer(sourceCode, separator);

    for (const std::string& token_str : tokenizer) {
        Token token;
        token.m_type = get_token_type(token_str);
        token.m_value = token_str;
        tokens.push_back(token);
    }

    return tokens;
}
