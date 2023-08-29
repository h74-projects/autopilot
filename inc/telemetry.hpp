#ifndef TELEMETRY_HPP
#define TELEMETRY_HPP

#include "variables.hpp"
#include "protocol.hpp"
#include "server.hpp"

#include <memory> // shared ptr
#include <string> // std::string
#include <cstdint> // uint32_t

namespace fgear {

class Telemetry {
public:
    Telemetry(std::shared_ptr<Protocol> a_protocol, std::unique_ptr<Server>&& a_server, std::string const& a_address = "127.0.0.1");
    ~Telemetry() = default;

    void run_telemetry();

private:
    std::shared_ptr<Protocol> m_protocol;
    std::unique_ptr<Server> m_server;
};

} // namespace fgear

#endif // TELEMETRY_HPP