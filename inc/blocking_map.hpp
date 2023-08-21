#ifndef BLOCKING_MAP_HPP
#define BLOCKING_MAP_HPP

#include <unordered_map> // map
#include <mutex> // mutex
#include <condition_variable> // conditional variables

namespace concurrency {

template<typename K, typename V>
class BlockingMap {
public:
    BlockingMap() = default;
    ~BlockingMap() = default;

    BlockingMap(BlockingMap&&) = delete;
    BlockingMap operator=(BlockingMap&&) = delete;

    V const& at(K const& a_key) const;

    void insert(K const& a_key, V const& a_value);

private:
    std::unordered_map<K, V> m_map;
    std::condition_variable m_cv;
    std::mutex m_mtx;
};

} // namespace concurrency

#include "inl/blocking_map.hxx"

#endif // BLOCKING_MAP_HPP