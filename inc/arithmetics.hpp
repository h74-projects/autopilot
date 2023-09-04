#ifndef ARITHMETICS_HPP
#define ARITHMETICS_HPP

#include "ast_node.hpp"

#include <memory> // unique ptr

namespace fgear {

class Arithmetics {
public:
    virtual ~Arithmetics() = default;

    virtual std::unique_ptr<ASTNode> op(std::unique_ptr<ASTNode> a_left, std::unique_ptr<ASTNode> a_right) = 0;

protected:
    Arithmetics() = default;
    Arithmetics(Arithmetics const&) = default;
    Arithmetics& operator=(Arithmetics const&) = default;
};

} // namespace fgear

#endif // ARITHMETICS_HPP