#ifndef TELEMETRY_HPP
#define TELEMETRY_HPP

#include "variables.hpp"
#include "protocol.hpp"
#include "server.hpp"

#include <memory> // shared ptr

namespace fgear {

class Telemetry {

private:
    std::shared_ptr<Variables> m_variables;
    std::shared_ptr<Protocol> m_protocol;
    std::unique_ptr<Server> m_server;
};

} // namespace fgear

#endif // TELEMETRY_HPP