#ifndef PROTOCOL_HPP
#define PROTOCOL_HPP

#include "variables.hpp"

#include <string> // std::string
#include <memory> // shared ptr

namespace fgear {

class Protocol {
public:
    Protocol(std::shared_ptr<Variables> a_variables);
    ~Protocol() = default;

    void unpack(std::string const& a_package);

private:
    std::shared_ptr<Variables> m_variables;
};

} // namespace fgear

#endif // PROTOCOL_HPP