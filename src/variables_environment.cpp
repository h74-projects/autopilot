#include "variables_environment.hpp"

namespace fgear {

Environment::Environment(std::unique_ptr<MiddleMan>&& a_middle_man)
: m_middle_man{std::move(a_middle_man)}
{
}

void Environment::load_binded(std::shared_ptr<Variables> a_binded)
{
    m_bind = a_binded;
}


void Environment::set(std::string const& a_key, float const& a_value)
{
    if (m_bind.get()->contains(a_key)) {
        std::string message{"set " + a_key + ' ' + std::to_string(a_value)};
        m_middle_man.get()->send_message(message);
        return;
    }
    m_local.set(a_key, a_value);
}


float Environment::get(std::string const& a_key) const
{
    if (m_bind.get()->contains(a_key)) {    
        return m_bind.get()->get(a_key);
    }
    return m_local.get(a_key);    
}

void Environment::insert(std::string const& a_key, float const& a_value)
{
    if (not m_local.contains(a_key)) {
        m_local.insert(a_key, a_value);
    }
    throw std::invalid_argument("variable already exists");
}


} // namespace fgear
