#ifndef VAR_HPP
#define VAR_HPP

#include <string>
#include <unordered_map>
#include <any>

class Var {
public:

    Var() = default;
    Var(Var const& a_other); 
    Var& operator=(Var const& a_other);

    template <typename T>
    Var(T const& a_value); 

    template <typename T>
    Var& operator=(T const& a_value); 

    template <typename T>
    operator T() const; 

    operator bool() const; 

    template <typename T>
    T operator+(Var const& a_other) const;

    template <typename T>
    Var operator-(Var const& a_other) const;

    template <typename T>
    Var operator*(Var const& a_other) const;

    template <typename T>
    Var operator/(Var const& a_other) const;

    // Comparison operators
    template <typename T>
    bool operator==(T const& a_other) const;

    template <typename T>
    bool operator!=(T const& a_other) const;

    template <typename T>
    bool operator<(Var const& a_other) const;

    template <typename T>
    bool operator>(Var const& a_other) const;

    template <typename T>
    bool operator<=(Var const& a_other) const;

    template <typename T>
    bool operator>=(Var const& a_other) const;

    std::string type_id() const noexcept; 

private:
    void set(std::string const& a_key, std::any const& a_value);
    std::any get(std::string const& a_key) const;
    template<typename T> 
    T get(std::string const& a_key) const;
    bool contains(std::string const& a_key) const;

private:
    std::unordered_map<std::string, std::any> m_varible_data_map;
};

#include "inl/var.hxx"

#endif // VAR_HPP
