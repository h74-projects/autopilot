#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include "ast_node.hpp"
#include "pugixml.hpp" // xml_doc
#include "ast_names.hpp"
#include "variables_environment.hpp"
#include "parser.hpp"

//courtsey of https://github.com/vivekbhadra/system_analyser/blob/main/SystemAnalyser/SystemAnalyser.h
#include "SystemAnalyser.hpp"

#include <string> // std string
#include <vector> // vector
#include <memory> // unique ptr

namespace fgear {

class Interpreter {
public:
    //TODO: build the environment
    Interpreter(std::string const& a_file_name, std::unique_ptr<Environment>&& a_environment);
    ~Interpreter() = default;

    std::shared_ptr<Variables> get_binded();

    void run();

private:
    friend ASTNode;
    friend ArithmeticNode;
    friend AssignmentNode;
    friend BindNode;
    friend ConditionNode;
    friend IfNode;
    friend PrintNode;
    friend VariableNode;
    friend SleepNode;

    void accept(std::unique_ptr<ASTNode> const& a_node);

    void bind_all();
    void send_generic_protocol();
    void create_xml();

    void nothing() {};

private:
    Parser m_parser;
    std::unique_ptr<Environment> m_environment;
    std::vector<std::unique_ptr<ASTNode>> m_program;
    pugi::xml_document m_doc;
    util::SystemAnalyser m_analyser;
    std::shared_ptr<Variables> m_variables;
};

} // namespace fgear

#endif // INTERPRETER_HPP