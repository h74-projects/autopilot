#include "mu_test.h"
#include "parser.hpp"
#include "lexer.hpp"

#include <fstream>

BEGIN_TEST(var_int_test)
    Lexer lexer;
    std::string sourceCode = "sleep 1000";

    std::vector<Token> tokens = lexer.tokenize(sourceCode);

    for (Token const& token : tokens) {
        std::string tokenType;
        if (token.m_type == TokenType::IDENTIFIER) {
            tokenType = "IDENTIFIER";
        } else if (token.m_type == TokenType::NUMBER) {
            tokenType = "NUMBER";
        } else if (token.m_type == TokenType::SYMBOL) {
            tokenType = "SYMBOL";
        }

        std::cout << "Token Type: " << tokenType << ", Value: " << token.m_value << std::endl;
    }
    ASSERT_PASS();
END_TEST

BEGIN_TEST(script_test)
    Lexer lexer;

    std::string sourceCode = " while rpm < 750 { print rpm sleep 250 }";

    std::vector<Token> tokens = lexer.tokenize(sourceCode);

   for (Token const& token : tokens) {
    std::string tokenType;

    switch (token.m_type) {
        case TokenType::VAR:
            tokenType = "VAR";
            break;
        case TokenType::BIND:
            tokenType = "BIND";
            break;
        case TokenType::IF:
            tokenType = "IF";
            break;
        case TokenType::ELSE:
            tokenType = "ELSE";
            break;
        case TokenType::WHILE:
            tokenType = "WHILE";
            break;
        case TokenType::IDENTIFIER:
            tokenType = "IDENTIFIER";
            break;
        case TokenType::NUMBER:
            tokenType = "NUMBER";
            break;
        // case TokenType::FLOAT_NUMBER:
        //     tokenType = "FLOAT_NUMBER";
        //     break;
        case TokenType::STRING_LITERAL:
            tokenType = "STRING_LITERAL";
            break;
        case TokenType::ASSIGNMENT:
            tokenType = "ASSIGNMENT";
            break;
        case TokenType::PLUS:
            tokenType = "PLUS";
            break;
        case TokenType::MINUS:
            tokenType = "MINUS";
            break;
        case TokenType::ASTERISK:
            tokenType = "ASTERISK";
            break;
        case TokenType::SLASH:
            tokenType = "SLASH";
            break;
        case TokenType::OPEN_PAREN:
            tokenType = "OPEN_PAREN";
            break;
        case TokenType::CLOSE_PAREN:
            tokenType = "CLOSE_PAREN";
            break;
        case TokenType::OPEN_SCOP:
            tokenType = "OPEN_SCOP";
            break;
        case TokenType::CLOSE_SCOP:
            tokenType = "CLOSE_SCOP";
            break;
        case TokenType::COLON:
            tokenType = "COLON";
            break;
        case TokenType::COMMA:
            tokenType = "COMMA";
            break;
        case TokenType::SEMICOLON:
            tokenType = "SEMICOLON";
            break;
         case TokenType::SYMBOL:
            tokenType = "SYMBOL";
            break;
         case TokenType::PRINT:
            tokenType = "PRINT";
            break;
         case TokenType::SLEEP:
            tokenType = "SLEEP";
            break;
        case TokenType::LESS_EQUAL:
            tokenType = "LESS_EQUAL";
            break;
        case TokenType::GREATER:
            tokenType = "LESS_EQUAL";
            break;
        case TokenType::GREATER_EQUAL:
            tokenType = "LESS_EQUAL";
            break;
        case TokenType::NOT_EQUAL:
            tokenType = "LESS_EQUAL";
            break;
        case TokenType::LESS:
            tokenType = "LESS";
            break;
        case TokenType::TELEMETRY:
            tokenType = "LESS";
            break;
        case TokenType::CONNECT:
            tokenType = "LESS";
            break;
    }

    std::cout << "Token Type: " << tokenType << ", Value: " << token.m_value << std::endl;
}

    ASSERT_PASS();
END_TEST

BEGIN_TEST(read_file_test)
    Lexer lexer;

    std::ifstream inputFile("script.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Failed to open script.txt" << std::endl;
    }

    std::string sourceCode((std::istreambuf_iterator<char>(inputFile)),
                            std::istreambuf_iterator<char>());

    inputFile.close();

    std::vector<Token> tokens = lexer.tokenize(sourceCode);

   for (Token const& token : tokens) {
    std::string tokenType;

    switch (token.m_type) {
        case TokenType::VAR:
            tokenType = "VAR";
            break;
        case TokenType::BIND:
            tokenType = "BIND";
            break;
        case TokenType::IF:
            tokenType = "IF";
            break;
        case TokenType::ELSE:
            tokenType = "ELSE";
            break;
        case TokenType::WHILE:
            tokenType = "WHILE";
            break;
        case TokenType::IDENTIFIER:
            tokenType = "IDENTIFIER";
            break;
        case TokenType::NUMBER:
            tokenType = "NUMBER";
            break;
        // case TokenType::FLOAT_NUMBER:
        //     tokenType = "FLOAT_NUMBER";
        //     break;
        case TokenType::STRING_LITERAL:
            tokenType = "STRING_LITERAL";
            break;
        case TokenType::ASSIGNMENT:
            tokenType = "ASSIGNMENT";
            break;
        case TokenType::PLUS:
            tokenType = "PLUS";
            break;
        case TokenType::MINUS:
            tokenType = "MINUS";
            break;
        case TokenType::ASTERISK:
            tokenType = "ASTERISK";
            break;
        case TokenType::SLASH:
            tokenType = "SLASH";
            break;
        case TokenType::OPEN_PAREN:
            tokenType = "OPEN_PAREN";
            break;
        case TokenType::CLOSE_PAREN:
            tokenType = "CLOSE_PAREN";
            break;
        case TokenType::OPEN_SCOP:
            tokenType = "OPEN_SCOP";
            break;
        case TokenType::CLOSE_SCOP:
            tokenType = "CLOSE_SCOP";
            break;
        case TokenType::COLON:
            tokenType = "COLON";
            break;
        case TokenType::COMMA:
            tokenType = "COMMA";
            break;
        case TokenType::SEMICOLON:
            tokenType = "SEMICOLON";
            break;
         case TokenType::SYMBOL:
            tokenType = "SYMBOL";
            break;
         case TokenType::PRINT:
            tokenType = "PRINT";
            break;
         case TokenType::SLEEP:
            tokenType = "SLEEP";
            break;
        case TokenType::LESS_EQUAL:
            tokenType = "LESS_EQUAL";
            break;
        case TokenType::GREATER:
            tokenType = "LESS_EQUAL";
            break;
        case TokenType::GREATER_EQUAL:
            tokenType = "LESS_EQUAL";
            break;
        case TokenType::NOT_EQUAL:
            tokenType = "LESS_EQUAL";
            break;
        case TokenType::LESS:
            tokenType = "LESS";
            break;
        case TokenType::TELEMETRY:
            tokenType = "LESS";
            break;
        case TokenType::CONNECT:
            tokenType = "LESS";
            break;
    }

    std::cout << "Token Type: " << tokenType << ", Value: " << token.m_value << std::endl;
}

    ASSERT_PASS();
END_TEST


BEGIN_TEST(parse_var)
    std::string sourceCode = "var x = 42";
    fg::Parser parser(sourceCode);
    
    auto vec_node = parser.parse();
    ASSERT_EQUAL(vec_node.size(), 1);
    auto name = dynamic_cast<VariableNode*>(vec_node.front().get());
    ASSERT_EQUAL( name->name() , "x");

END_TEST

BEGIN_TEST(parse_bind)
    std::string sourceCode = "var x = bind ( '/sim/flightmodel/position/elevation-ft' ) ";
    fg::Parser parser(sourceCode);
    
    auto vec_node = parser.parse();
    ASSERT_EQUAL(vec_node.size(), 1);
    auto name = dynamic_cast<BindNode*>(vec_node.front().get());
    ASSERT_EQUAL( name->name() , "x");

END_TEST

BEGIN_TEST(print_var)
    std::string sourceCode = "print 'hello_world' ";
    fg::Parser parser(sourceCode);
    
    auto vec_node = parser.parse();
    ASSERT_EQUAL(vec_node.size(), 1);
    auto name = dynamic_cast<PrintNode*>(vec_node.front().get());
    ASSERT_EQUAL( name->text() , "'hello_world'");

END_TEST

BEGIN_TEST(sleep_var)
    std::string sourceCode = "sleep 5000 ";
    fg::Parser parser(sourceCode);
    
    auto vec_node = parser.parse();
    ASSERT_EQUAL(vec_node.size(), 1);
    auto name = dynamic_cast<SleepNode*>(vec_node.front().get());
    ASSERT_EQUAL( name->time() , 5000);

END_TEST

BEGIN_TEST(while_var)
    std::string sourceCode = "while rpm < 750 { var rpm = 750 }";
    fg::Parser parser(sourceCode);
    
    auto vec_node = parser.parse();
    ASSERT_EQUAL(vec_node.size(), 1);
    //auto name = dynamic_cast<WhileNode*>(vec_node.front().get());
    // ASSERT_EQUAL( name->time() , 5000);

END_TEST


TEST_SUITE(因果応報 [inga ōhō: bad causes bring bad results])
    TEST(var_int_test)
    TEST(script_test)
    TEST(read_file_test)
    TEST(parse_var)
    TEST(parse_bind)
    TEST(print_var)
    TEST(sleep_var)
    IGNORE_TEST(while_var)

END_SUITE