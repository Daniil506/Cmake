#pragma once
#include <cstddef>
#include <stdexcept>

template <typename T>
class Queue {
    T* _data;
    size_t _count;
    size_t _size;
    size_t _front;
    size_t _back;

public:
    Queue(size_t _size = 1);
    Queue(const Queue& other);
    ~Queue();

    inline size_t size() const noexcept;
    T& front();
    inline bool is_empty() const noexcept;
    inline bool is_full() const noexcept;
    void push(const T& elem);
    T pop();
};

template <typename T>
Queue<T>::Queue(size_t _size)
    : _size(_size), _count(0), _front(0), _back(0) {
    _data = new T[_size];
}

template <typename T>
Queue<T>::Queue(const Queue& other)
    : _size(other._size),
    _count(other._count),
    _front(0),
    _back(other._size == 0 ? 0 : other._count % other._size) {

    _data = new T[_size];

    for (size_t i = 0; i < _count; i++) {
        size_t circle_id = (other._front + i) % other._size;
        _data[i] = other._data[circle_id];
    }
}

template <typename T>
Queue<T>::~Queue() {
    delete[] _data;
}

template <typename T>
void Queue<T>::push(const T& elem) {
    if (is_full()) {
        throw std::out_of_range("Queue is full");
    }

    _data[_back] = elem;
    _back = (_back + 1) % _size;
    _count++;
}

template <typename T>
T Queue<T>::pop() {
    if (is_empty()) {
        throw std::out_of_range("Queue is empty");
    }

    T popped = _data[_front];
    _front = (_front + 1) % _size;
    _count--;

    return popped;
}

template <typename T>
inline bool Queue<T>::is_empty() const noexcept {
    return _count == 0;
}

template <typename T>
inline bool Queue<T>::is_full() const noexcept {
    return _count == _size;
}

template <typename T>
inline size_t Queue<T>::size() const noexcept {
    return _count;
}

template <typename T>
T& Queue<T>::front() {
    if (is_empty()) {
        throw std::out_of_range("Queue is empty");
    }

    return _data[_front];
}