#include "../blocking_map.hpp"

namespace concurrency {

template<typename K, typename V>
std::atomic<V>& BlockingMap<K, V>::at(K const& a_key)
{
    std::unique_lock lock(m_mtx);
    return m_map.at(a_key);
}

template<typename K, typename V>
std::atomic<V> const& BlockingMap<K, V>::at(K const& a_key) const
{
    std::unique_lock lock(m_mtx);
    return m_map.at(a_key);
}
 
template<typename K, typename V>
std::atomic<V>& BlockingMap<K, V>::operator[](K const& a_key)
{
    std::unique_lock lock(m_mtx);
    return m_map[a_key];
}

template<typename K, typename V>
bool BlockingMap<K, V>::contains(K const& a_key) const noexcept
{
    std::unique_lock lock(m_mtx);
    return m_map.find(a_key) != m_map.end();
}

template<typename K, typename V>
V BlockingMap<K, V>::read(K const& a_key) const
{
    std::unique_lock lock(m_mtx);
    return m_map.at(a_key).load();        
}

} // namespace concurrency
