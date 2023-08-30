#ifndef VARIABLES_HPP
#define VARIABLES_HPP

#include "blocking_map.hpp"

#include <string> //std::string
#include <atomic> // std::atomic<float>

namespace fgear {

class Variables {
public:
    Variables() = default;
    ~Variables() = default;

    //insert new element, will throw exception if element already exists
    void insert(std::string const& a_key, float a_value);

    //sets existing element
    void set(std::string const& a_key, float a_value);

    //change value in map if current value is different than new value
    void exchange_if(std::string const& a_key, float a_value);

    //get existing element
    float get(std::string const& a_key);

private:
    concurrency::BlockingMap<std::string, std::atomic<float>> m_map;
    mutable std::mutex m_tx;
    // concurrency::BlockingMap<std::string, float> m_map;
};

} // namespace fgear

#endif // VARIABLES_HPP