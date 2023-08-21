#ifndef BLOCKING_MAP_HPP
#define BLOCKING_MAP_HPP

#include <unordered_map> // map
#include <mutex> // mutex
#include <condition_variable> // conditional variables

namespace concurrency {

template<typename T, typename U>
class BlockingMap {
public:
    BlockingMap() = default;
    ~BlockingMap() = default;

    BlockingMap(BlockingMap&&) = delete;
    BlockingMap operator=(BlockingMap&&) = delete;

private:
    std::unordered_map<T, U> m_map;
    std::condition_variable m_cv;
    std::mutex m_mtx;
};

} // namespace concurrency

#endif // BLOCKING_MAP_HPP