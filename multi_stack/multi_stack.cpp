#include "multi_stack.h"
template <typename T>
MultiStack<T>::MultiStack(size_t n, size_t size) {
    _N = n;
    _total_size = size;
    _count = 0;

   