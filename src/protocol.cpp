#include "protocol.hpp"

namespace fgear {

Protocol::Protocol(std::shared_ptr<Variables> a_variables)
: m_variables(a_variables)
{
}

void Protocol::unpack(std::string const& a_package)
{
    size_t name_index{};
    size_t value_index = a_package.find(":") + 1;
    size_t end_index = a_package.find(",");
    size_t size = m_variables.get()->size();
    for (size_t i = 0; i < size; ++i) {
        std::string name = a_package.substr(name_index, value_index - 1 - name_index);
        float value = std::stof(a_package.substr(value_index, end_index - value_index));
        m_variables.get()->exchange_if(name, value);
        name_index = end_index + 1;
        value_index = a_package.find(":", name_index) + 1;
        end_index = a_package.find(",", name_index);
        name.clear();
    }
}

} // namespace fgear
