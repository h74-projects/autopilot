#ifndef BLOCKING_MAP_HPP
#define BLOCKING_MAP_HPP

#include <unordered_map> // map
#include <mutex> // mutex
#include <condition_variable> // conditional variables
#include <atomic> // atomic

namespace concurrency {

template<typename K, typename V>
class BlockingMap {
public:
    BlockingMap() = default;
    ~BlockingMap() = default;

    BlockingMap(BlockingMap const&) = delete;
    BlockingMap operator=(BlockingMap const&) = delete;

    BlockingMap(BlockingMap&&) = delete;
    BlockingMap operator=(BlockingMap&&) = delete;

    V& at(K const& a_key);
    V const& at(K const& a_key) const;

    V& operator[](K const& a_key);

    bool contains(K const& a_key) const noexcept;

    void print() const;

private:
    std::unordered_map<K, V> m_map;
    //TODO: decide if necessary
    //std::condition_variable m_cv;
    
    mutable std::mutex m_mtx;
};

} // namespace concurrency

#include "inl/blocking_map.hxx"

#endif // BLOCKING_MAP_HPP