#include "../blocking_map.hpp"

#include <type_traits> // enable_if
#include <iostream> // cout

namespace concurrency {

template<typename K, typename V>
V& BlockingMap<K, V>::at(K const& a_key)
{
    std::unique_lock lock{m_mtx};
    return m_map.at(a_key);
}

template<typename K, typename V>
V const& BlockingMap<K, V>::at(K const& a_key) const
{
    std::unique_lock lock{m_mtx};
    return m_map.at(a_key);
}
 
template<typename K, typename V>
V& BlockingMap<K, V>::operator[](K const& a_key)
{
    std::unique_lock lock{m_mtx};
    return m_map[a_key];
}

template<typename K, typename V>
bool BlockingMap<K, V>::contains(K const& a_key) const noexcept
{
    std::unique_lock lock{m_mtx};
    return m_map.find(a_key) != m_map.end();
}

// template<typename K, typename V>
// void BlockingMap<K, V>::print() const
// {
//     std::unique_lock lock{m_mtx};
//     for (auto& it : m_map) {
//         std::cout "key: " << it->key() << " value: " << it->value() << '\n';
//     }
    
// }

template<typename K, typename V>
void BlockingMap<K, V>::print() const
{
    std::unique_lock lock{m_mtx};
    auto begin = m_map.cbegin();
    auto end = m_map.cend();
    while (begin != end) {
        std::cout << "key: " << begin->first << " value: " << begin->second.load() << '\n';
        ++begin;
    }
    
}


} // namespace concurrency
