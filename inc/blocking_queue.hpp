#ifndef BLOCKING_QUEUE_HPP
#define BLOCKING_QUEUE_HPP

#include <cstddef> // size_t
#include <queue> // data
#include <condition_variable> //class member
#include <thread> //class member
#include <memory> //unique ptr

namespace thread {

template<typename T>
class BlockingQueue {
public:
    explicit BlockingQueue(size_t a_capacity);
    ~BlockingQueue() = default;

    BlockingQueue(BlockingQueue const&) = delete;
    BlockingQueue& operator=(BlockingQueue const&) = delete;

    BlockingQueue(BlockingQueue &&) = delete;
    BlockingQueue& operator=(BlockingQueue &&) = delete;

    void enqueue(T const& a_item);
    void enqueue(T&& a_item);

    void dequeue(T& a_reciever);
    
    void dequeue(std::unique_ptr<T>& a_reciever);

    size_t size() const;

    bool full() const;
    bool empty() const;

private:
    std::queue<T> m_data;
    size_t m_capacity;
    mutable std::mutex m_mtx;
    std::condition_variable m_enqueue;
    std::condition_variable m_dequeue;
};


} // namespace thread

#include "inl/blocking_queue.hxx"

#endif // BLOCKING_QUEUE_HPP