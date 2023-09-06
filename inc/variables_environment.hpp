#ifndef VARIABLES_ENVIRONMENT_HPP
#define VARIABLES_ENVIRONMENT_HPP

#include "variables.hpp"
#include "telemetry.hpp"
#include "middle_man.hpp"

#include <memory> // shared and unique ptr
#include <string> // std::string

namespace fgear {

class Environment {
public:
    explicit Environment(std::unique_ptr<MiddleMan>&& a_middle_man);
    ~Environment() = default;

    Environment(Environment const&) = delete;
    Environment(Environment&&) = delete;

    Environment& operator=(Environment const&) = delete;
    Environment& operator=(Environment&&) = delete;

    void load_binded(std::shared_ptr<Variables> a_binded);

    void set(std::string const& a_key, float const& a_value);
    void insert(std::string const& a_key, float const& a_value);
    
    float get(std::string const& a_key) const;

private:
    std::unique_ptr<MiddleMan> m_middle_man;
    std::shared_ptr<Variables> m_bind;
    Variables m_local;
};

} // namespace fgear

#endif // VARIABLES_ENVIRONMENT_HPP