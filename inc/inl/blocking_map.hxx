#include "../blocking_map.hpp"

namespace concurrency {

template<typename K, typename V>
V const& BlockingMap<K, V>::at(K const& a_key) const
{
    std::unique_lock lock(m_mtx);
    return m_map.at(a_key);
}

template<typename K, typename V>
void BlockingMap<K, V>::write(K const& a_key, V const& a_value)
{
    std::unique_lock lock(m_mtx);
    m_map[a_key] = a_value;
}

template<typename K, typename V>
bool BlockingMap<K, V>::contains(K const& a_key) const noexcept
{
    std::unique_lock lock(m_mtx);
    return m_map.find(a_key) != m_map.end();
}

} // namespace concurrency
