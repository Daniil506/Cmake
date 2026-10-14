// Copyright 2026 Daniil

#ifndef LIB_VECTOR_ITERATOR_H_
#define LIB_VECTOR_ITERATOR_H_

#include <cstddef>

namespace vector_lib {

    template <typename T>
    class Iterator {
    public:
        Iterator() : ptr_(nullptr) {}
        explicit Iterator(T* ptr) : ptr_(ptr) {}

        T& operator*() const { return *ptr_; }
        T* operator->() const { return ptr_; }

        Iterator& operator++() {
            ++ptr_;
            return *this;
        }
        Iterator operator++(int) {
            Iterator tmp(*this);
            ++ptr_;
            return tmp;
        }
        Iterator& operator--() {
            --ptr_;
            return *this;
        }
        Iterator operator--(int) {
            Iterator tmp(*this);
            --ptr_;
            return tmp;
        }

        Iterator& operator+=(std::ptrdiff_t n) {
            ptr_ += n;
            return *this;
        }
        Iterator& operator-=(std::ptrdiff_t n) {
            ptr_ -= n;
            return *this;
        }
        Iterator operator+(std::ptrdiff_t n) const {
            return Iterator(ptr_ + n);
        }
        Iterator operator-(std::ptrdiff_t n) const {
            return Iterator(ptr_ - n);
        }
        std::ptrdiff_t operator-(const Iterator& other) const {
            return ptr_ - other.ptr_;
        }

        bool operator==(const Iterator& other) const {
            return ptr_ == other.ptr_;
        }
        bool operator!=(const Iterator& other) const {
            return ptr_ != other.ptr_;
        }
        bool operator<(const Iterator& other) const {
            return ptr_ < other.ptr_;
        }
        bool operator>(const Iterator& other) const {
            return ptr_ > other.ptr_;
        }
        bool operator<=(const Iterator& other) const {
            return ptr_ <= other.ptr_;
        }
        bool operator>=(const Iterator& other) const {
            return ptr_ >= other.ptr_;
        }

    private:
        T* ptr_;
    };

}  // namespace vector_lib

#endif  // LIB_VECTOR_ITERATOR_H_