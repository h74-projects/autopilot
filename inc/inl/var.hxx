#ifndef VAR_HXX
#define VAR_HXX

#include "var.hpp"
#include <any>
#include <stdexcept>

inline Var::Var(Var const& a_other)
: m_varible_data_map(a_other.m_varible_data_map) 
{
}

inline Var& Var::operator=(Var const& a_other) 
{
    if (this != &a_other) {
        m_varible_data_map = a_other.m_varible_data_map;
    }
    return *this;
}

template <typename T>
inline Var::Var(T const& a_value) 
{
    set("value", a_value);
}

template <typename T>
inline Var& Var::operator=(T const& a_value) 
{
    set("value", a_value);
    return *this;
}

inline Var::operator bool() const 
{
    if (contains("value")) {
        return std::any_cast<bool>(get("value"));
    }
    return false;
}

template <typename T>
inline Var::operator T() const 
{
    if (contains("value")) {
        return std::any_cast<T>(get("value"));
    }
    throw std::bad_cast();
}

inline std::string Var::type_id() const noexcept
{
    try {
        std::any value = m_varible_data_map.at("value");
            return value.type().name();
    } catch (const std::out_of_range&) {
            return "empty";
    }    
}

inline void Var::set(const std::string& a_key, std::any const& a_value) 
{
    m_varible_data_map[a_key] = a_value;
}

inline std::any Var::get(std::string const& a_key) const 
{
    if (m_varible_data_map.count(a_key) == 0) {
        throw std::out_of_range("Key not found");
    }
    return m_varible_data_map.at(a_key);
}

template<typename T>
inline T Var::get(std::string const& a_key) const 
{
    return std::any_cast<T>(get(a_key));
}

inline bool Var::contains(std::string const& a_key) const 
{
    return m_varible_data_map.count(a_key) > 0;
}

// Arithmetic operators
template <typename T>
inline T Var::operator+(Var const& a_other) const
{
    if (type_id() == typeid(T).name()) {
        return T(std::any_cast<T>(get("value")) + a_other);
    }
    throw std::invalid_argument("Incompatible types for operator +");
}

template <typename T>
inline Var Var::operator-(Var const& a_other) const
{
    if (type_id() == typeid(T).name()) {
        return Var(std::any_cast<T>(get("value")) - a_other);
    }
    throw std::invalid_argument("Incompatible types for operator -");
}

template <typename T>
inline Var Var::operator*(Var const& a_other) const
{
    if (type_id() == typeid(T).name()) {
        return Var(std::any_cast<T>(get("value")) * a_other);
    }
    throw std::invalid_argument("Incompatible types for operator *");
}

template <typename T>
inline Var Var::operator/(Var const& a_other) const
{
    if (type_id() == typeid(T).name()) {
        return Var(std::any_cast<T>(get("value")) / a_other);
    }
    throw std::invalid_argument("Incompatible types for operator /");
}

// Comparison operators
template <typename T>
inline bool Var::operator==(T const& a_other) const
{
    if (type_id() == typeid(T).name()) {
        return std::any_cast<T>(get("value")) == a_other;
    }
    return false;
}

template <typename T>
inline bool Var::operator!=(T const& a_other) const
{
    return !(*this == a_other);
}

template <typename T>
inline bool Var::operator<(Var const& a_other) const
{
    if (type_id() == typeid(T).name()) {
        return std::any_cast<T>(get("value")) < a_other;
    }
    throw std::invalid_argument("Incompatible types for operator <");
}

template <typename T>
inline bool Var::operator>(Var const& a_other) const
{
    return a_other < *this;
}

template <typename T>
inline bool Var::operator<=(Var const& a_other) const
{
    return !(*this > a_other);
}

template <typename T>
inline bool Var::operator>=(Var const& a_other) const
{
    return !(*this < a_other);
}

#endif // VAR_HXX
