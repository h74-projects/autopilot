#ifndef MEDIATOR_HPP
#define MEDIATOR_HPP

#include <string> // std::string

namespace fgear {

class Mediator {
public:
    virtual ~Mediator() = default;

    //TODO: change to an actual Var class once it's completed
    virtual void set(typename Var) = 0;

    //TODO: change to an actual Var class once it's completed
    virtual typename Var get(std::string const& a_key) = 0; 

protected:
    Mediator() = default;
    Mediator(Mediator const&) = default;
    Mediator& operator=(Mediator const&) = default;
};

} // namespace fgear

#endif // MEDIATOR_HPP