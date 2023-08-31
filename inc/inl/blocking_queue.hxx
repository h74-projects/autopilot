#include "../blocking_queue.hpp"

#include <chrono>
namespace thread {
template<typename T>
BlockingQueue<T>::BlockingQueue(size_t a_capacity)
: m_data{}
, m_capacity{a_capacity}
, m_mtx{}
, m_enqueue{}
, m_dequeue{}
{
}

template<typename T>
void BlockingQueue<T>::enqueue(T const& a_item)
{
    std::unique_lock<std::mutex> lock(m_mtx);
    while (m_data.size() == m_capacity) {
        m_enqueue.wait(lock);
    }
    m_data.push(a_item);
    m_dequeue.notify_all(); 
}

template<typename T>
void BlockingQueue<T>::enqueue(T&& a_item)
{
    std::unique_lock<std::mutex> lock(m_mtx);
    while (m_data.size() == m_capacity) {
        m_enqueue.wait(lock);
    }
    m_data.emplace(std::move(a_item));
    m_dequeue.notify_all(); 
}

template<typename T>
void BlockingQueue<T>::dequeue(T& a_reciever)
{
    std::unique_lock<std::mutex> lock(m_mtx);
    while (m_data.empty()) {
        m_dequeue.wait(lock);  
    }
    a_reciever = std::move(m_data.front());
    m_data.pop();
    m_enqueue.notify_all();
}

// template<typename T>
// void BlockingQueue<T>::dequeue(std::unique_ptr<T>& a_reciever)
// {
//     std::unique_lock<std::mutex> lock(m_mtx);
//     while (m_data.empty()) {
//         m_dequeue.wait(lock);  
//     }
//     a_reciever = m_data.front();
//     m_data.pop();
//     m_enqueue.notify_all();
// }

template<typename T>
size_t BlockingQueue<T>::size() const
{
    std::unique_lock<std::mutex> lock(m_mtx);
    return m_data.size();    
}


template<typename T>
bool BlockingQueue<T>::full() const
{
    std::unique_lock<std::mutex> lock(m_mtx);
    return m_data.size() == m_capacity;
}

template<typename T>
bool BlockingQueue<T>::empty() const
{
    std::unique_lock<std::mutex> lock(m_mtx);
    return m_data.size() == 0;
}

} // namespace thread
