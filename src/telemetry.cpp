#include "telemetry.hpp"

namespace fgear {

Telemetry::Telemetry(std::shared_ptr<Protocol> a_protocol, std::unique_ptr<Server>&& a_server, std::string const& a_address)
: m_protocol{a_protocol}
, m_server{std::move(a_server)}
{
    m_server.get()->connect(a_address);
}

void Telemetry::run_telemetry()
{
    m_server.get()->start_listening(m_protocol);
}

} //namespace fgear
