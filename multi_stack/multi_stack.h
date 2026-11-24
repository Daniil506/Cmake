// Copyright 2026 Daniil506

#ifndef MULTI_STACK_MULTI_STACK_H_
#define MULTI_STACK_MULTI_STACK_H_

#include <cstddef>

template <typename T>
class MultiStack {
 private:
    void* _raw_memory;
    T* _data;
    size_t* _L;
    size_t* _R;
    size_t* _tops;
    size_t _N;
    size_t _total_size;
    size_t _count;

 public:
    MultiStack(size_t n, size_t size);
    ~MultiStack();

    MultiStack(const MultiStack&) = delete;
    MultiStack& operator=(const MultiStack&) = delete;

    void push(size_t n, const T& val);
    T pop(size_t n);
    T& top(size_t n);

    bool is_empty() const;
    bool is_full() const;
    bool is_empty(size_t n) const;
    bool is_full(size_t n) const;
};

#endif  // MULTI_STACK_MULTI_STACK_H_
