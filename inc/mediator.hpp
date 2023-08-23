#ifndef MEDIATOR_HPP
#define MEDIATOR_HPP

#include "var.hpp"

#include <string> // std::string

namespace fgear {

class Mediator {
public:
    virtual ~Mediator() = default;

    virtual void set(std::string const& a_key ,Var const& a_var) = 0;

    //virtual Var get(std::string const& a_key) = 0; 

protected:
    Mediator() = default;
    Mediator(Mediator const&) = default;
    Mediator& operator=(Mediator const&) = default;
};

} // namespace fgear

#endif // MEDIATOR_HPP