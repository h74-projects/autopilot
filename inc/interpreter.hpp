#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include "ast_node.hpp"
#include "pugixml.hpp" // xml_doc
#include "ast_names.hpp"
#include "variables_environment.hpp"
#include "parser.hpp"


#include <string> // std string
#include <vector> // vector
#include <memory> // unique ptr

namespace fgear {

class Interpreter {
public:
    Interpreter(std::string const& a_file_name, std::unique_ptr<Environment>&& a_environment);
    ~Interpreter() = default;
    
    void run_script();

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

    void create_xml();

    void accept(std::unique_ptr<ASTNode> a_node);

    void bind_all();
    void send_generic_protocol();

private:
    Parser m_parser;
    std::unique_ptr<Environment> m_environment;
    std::vector<std::unique_ptr<ASTNode>> m_program;
    pugi::xml_document m_doc;
};

} // namespace fgear

#endif // INTERPRETER_HPP