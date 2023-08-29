#include "variables.hpp"

#include <exception> // exceptions
#include <stdexcept> // std exceptions
#include <cmath> // abs


namespace fgear {

namespace {

bool compare_floats(float a_first, float a_second)
{
    constexpr float EPSILON = 0.0000001;
    return std::abs(a_first - a_second) > EPSILON;
}

} // namespace



void Variables::insert(std::string const& a_key, float a_value)
{
    if (m_map.contains(a_key)) {
        throw std::invalid_argument("key already exists");
    }
    m_map[a_key].store(a_value);
}

void Variables::set(std::string const& a_key, float a_value)
{
    m_map.at(a_key).store(a_value);
}

void Variables::exchange_if(std::string const& a_key, float a_value)
{
    if(compare_floats(m_map.at(a_key).load(), a_value)) {
        m_map.at(a_key).exchange(a_value);
    }
}


float Variables::get(std::string const& a_key)
{
    return m_map.at(a_key).load();
}

} // namespace fgear
