// Copyright 2026 Daniil

#ifndef LIB_VECTOR_TVECTOR_H_
#define LIB_VECTOR_TVECTOR_H_

#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <random>
#include <stdexcept>
#include <utility>

#include "Iterator.h"
#include "TMemData.h"

namespace vector_lib {

enum class Direction { kLeft, kRight };

template <typename T>
class Vector {
 public:
    explicit Vector(std::size_t size = 0);
    Vector(std::initializer_list<T> data);
    Vector(T* data, std::size_t size);
    Vector(const Vector<T>& other);
    Vector(Vector<T>&& other);
    ~Vector() = default;

    bool IsEmpty() const noexcept;
    bool IsFull() const noexcept;

    std::size_t Size() const noexcept;
    std::size_t Capacity() const noexcept;
    T Front() const;
    T Back() const;

    T& Front();
    T& Back();

    void PushFront(T element);
    void PushBack(T element);
    void Insert(T element, std::size_t human_index);

    void PopFront(std::size_t count = 1);
    void PopBack(std::size_t count = 1);
    void Erase(std::size_t human_index, std::size_t count = 1);

    void PushFront(std::initializer_list<T> data);
    void PushBack(std::initializer_list<T> data);
    void Insert(std::initializer_list<T> data, std::size_t human_index);

    Vector<T>& operator=(const Vector<T>& other);
    Vector<T>& operator=(Vector<T>&& other);

    const T& operator[](std::size_t human_index) const noexcept;
    T& operator[](std::size_t human_index) noexcept;

    template <typename U>
    friend std::ostream& operator<<(std::ostream& os, const Vector<U>& vec);

    template <typename U>
    friend std::istream& operator>>(std::istream& is, Vector<U>& vec);

    void Shuffle() noexcept;
    void SelectionSort() noexcept;

    Iterator<T> Begin() { return Iterator<T>(mem_.data_ + front_); }
    Iterator<T> End() { return Iterator<T>(mem_.data_ + front_ + mem_.size_); }

 private:
    void PushElementsToInsert(std::size_t human_index, Direction direction,
                              std::size_t count = 1);
    void PushElementsToErase(std::size_t human_index, Direction direction,
                             std::size_t count = 1);
    void ResetMemory(std::size_t new_size);
    void Clear();

    TMemData<T> mem_;
    std::size_t front_;
    std::size_t back_;
};

template <typename T>
std::size_t Vector<T>::Size() const noexcept {
    return mem_.size_;
}

template <typename T>
std::size_t Vector<T>::Capacity() const noexcept {
    return mem_.capacity_;
}

template <typename T>
T Vector<T>::Front() const {
    if (mem_.size_ == 0) {
        throw std::out_of_range("Vector::Front: empty vector");
    }
    return mem_.data_[front_];
}

template <typename T>
T Vector<T>::Back() const {
    if (mem_.size_ == 0) {
        throw std::out_of_range("Vector::Back: empty vector");
    }
    return mem_.data_[back_];
}

template <typename T>
bool Vector<T>::IsEmpty() const noexcept {
    return mem_.IsEmpty();
}

template <typename T>
bool Vector<T>::IsFull() const noexcept {
    return mem_.IsFull();
}

template <typename T>
T& Vector<T>::Front() {
    if (mem_.size_ == 0) {
        throw std::out_of_range("Vector::Front: empty vector");
    }
    return mem_.data_[front_];
}

template <typename T>
T& Vector<T>::Back() {
    if (mem_.size_ == 0) {
        throw std::out_of_range("Vector::Back: empty vector");
    }
    return mem_.data_[back_];
}

template <typename T>
Vector<T>::Vector(std::size_t size)
: mem_(size), front_(0), back_(size == 0 ? 0 : size - 1) {}

template <typename T>
Vector<T>::Vector(std::initializer_list<T> data)
: mem_(data), front_(0), back_(mem_.size_ == 0 ? 0 : mem_.size_ - 1) {}

template <typename T>
Vector<T>::Vector(T* data, std::size_t size)
: mem_(data, size),
front_(0),
back_(mem_.size_ == 0 ? 0 : mem_.size_ - 1) {}

template <typename T>
Vector<T>::Vector(const Vector<T>& other)
: mem_(other.mem_.size_),
front_(0),
back_(other.mem_.size_ == 0 ? 0 : other.mem_.size_ - 1) {
    for (std::size_t i = 0; i < other.mem_.size_; ++i) {
        std::size_t other_index = (other.front_ + i) % other.mem_.capacity_;
        mem_.data_[i] = other.mem_.data_[other_index];
    }
    mem_.size_ = other.mem_.size_;
}

template <typename T>
Vector<T>::Vector(Vector<T>&& other)
: mem_(std::move(other.mem_)), front_(other.front_), back_(other.back_) {
    other.front_ = 0;
    other.back_ = 0;
}

template <typename T>
void Vector<T>::PushFront(T element) {
    if (IsEmpty()) {
        front_ = 0;
        back_ = 0;
        mem_.data_[front_] = element;
        mem_.size_ = 1;
        return;
    }
    if (IsFull()) {
        ResetMemory(mem_.size_ + 1);
        front_ = mem_.capacity_ - 1;
        mem_.data_[front_] = element;
        ++mem_.size_;
        return;
    }
    front_ = (front_ == 0) ? mem_.capacity_ - 1 : front_ - 1;
    mem_.data_[front_] = element;
    ++mem_.size_;
}

template <typename T>
void Vector<T>::PushBack(T element) {
    if (IsEmpty()) {
        front_ = 0;
        back_ = 0;
        mem_.data_[front_] = element;
        mem_.size_ = 1;
        return;
    }
    if (IsFull()) {
        ResetMemory(mem_.size_ + 1);
        back_ = mem_.size_;
        mem_.data_[back_] = element;
        ++mem_.size_;
        return;
    }
    back_ = (back_ == mem_.capacity_ - 1) ? 0 : back_ + 1;
    mem_.data_[back_] = element;
    ++mem_.size_;
}

template <typename T>
void Vector<T>::Insert(T element, std::size_t human_index) {
    if (human_index > mem_.size_) {
        throw std::out_of_range("Vector::Insert: index out of range");
    }
    if (IsFull()) {
        ResetMemory(mem_.size_ + 1);
    }
    if (IsEmpty() && human_index != 0) {
        throw std::out_of_range("Vector::Insert: index out of range");
    }
    if (human_index == 0) {
        PushFront(element);
        return;
    }
    if (human_index == mem_.size_) {
        PushBack(element);
        return;
    }

    Direction direction =
        (human_index < mem_.size_ / 2) ? Direction::kLeft : Direction::kRight;

    PushElementsToInsert(human_index, direction);
    std::size_t real_index = (front_ + human_index) % mem_.capacity_;
    mem_.data_[real_index] = element;
    ++mem_.size_;
}

template <typename T>
void Vector<T>::PopFront(std::size_t count) {
    if (mem_.size_ < count) {
        throw std::out_of_range("Vector::PopFront: too many elements");
    }
    front_ = (front_ + count) % mem_.capacity_;
    mem_.size_ -= count;
    if (CalculateCapacity(mem_.size_) < mem_.capacity_) {
        ResetMemory(mem_.size_);
    }
}

template <typename T>
void Vector<T>::PopBack(std::size_t count) {
    if (mem_.size_ < count) {
        throw std::out_of_range("Vector::PopBack: too many elements");
    }
    back_ = (back_ - count + mem_.capacity_) % mem_.capacity_;
    mem_.size_ -= count;
    if (CalculateCapacity(mem_.size_) < mem_.capacity_) {
        ResetMemory(mem_.size_);
    }
}

template <typename T>
void Vector<T>::Erase(std::size_t human_index, std::size_t count) {
    if (human_index >= mem_.size_) {
        throw std::out_of_range("Vector::Erase: index out of range");
    }
    if (mem_.size_ < count) {
        throw std::out_of_range("Vector::Erase: too many elements");
    }
    if (human_index + count > mem_.size_) {
        throw std::out_of_range("Vector::Erase: range out of bounds");
    }
    if (human_index == 0) {
        PopFront(count);
        return;
    }
    if (human_index == mem_.size_ - 1) {
        PopBack(count);
        return;
    }

    std::size_t left_count = human_index;
    std::size_t right_count = mem_.size_ - human_index - count;
    Direction direction =
        (right_count <= left_count) ? Direction::kLeft : Direction::kRight;

    PushElementsToErase(human_index, direction, count);
    mem_.size_ -= count;
    if (CalculateCapacity(mem_.size_) < mem_.capacity_) {
        ResetMemory(mem_.size_);
    }
}

template <typename T>
void Vector<T>::PushFront(std::initializer_list<T> data) {
    if (IsEmpty()) {
        front_ = 0;
        back_ = data.size() - 1;
    }
    if (mem_.size_ + data.size() > mem_.capacity_) {
        ResetMemory(mem_.size_ + data.size());
        front_ = 0;
        back_ = mem_.size_ + data.size() - 1;
    }
    front_ = (front_ - data.size() + mem_.capacity_) % mem_.capacity_;
    std::size_t index = front_;
    for (const T& element : data) {
        mem_.data_[index] = element;
        index = (index + 1) % mem_.capacity_;
    }
    mem_.size_ += data.size();
}

template <typename T>
void Vector<T>::PushBack(std::initializer_list<T> data) {
    if (IsEmpty()) {
        front_ = 0;
        back_ = data.size() - 1;
    }
    if (mem_.size_ + data.size() > mem_.capacity_) {
        ResetMemory(mem_.size_ + data.size());
        front_ = 0;
        back_ = mem_.size_ - 1;
    }
    std::size_t index = (mem_.size_ == 0) ? 0 : (back_ + 1) % mem_.capacity_;
    back_ = (back_ + data.size()) % mem_.capacity_;
    for (const T& element : data) {
        mem_.data_[index] = element;
        index = (index + 1) % mem_.capacity_;
    }
    mem_.size_ += data.size();
}

template <typename T>
void Vector<T>::Insert(std::initializer_list<T> data, std::size_t human_index) {
    if (human_index > mem_.size_) {
        throw std::out_of_range("Vector::Insert: index out of range");
    }
    if (mem_.size_ + data.size() > mem_.capacity_) {
        ResetMemory(mem_.size_ + data.size());
    }
    if (IsEmpty() && human_index != 0) {
        throw std::out_of_range("Vector::Insert: index out of range");
    }
    if (human_index == 0) {
        PushFront(data);
        return;
    }
    if (human_index == mem_.size_) {
        PushBack(data);
        return;
    }

    Direction direction =
        (human_index < mem_.size_ / 2) ? Direction::kLeft : Direction::kRight;

    PushElementsToInsert(human_index, direction, data.size());
    std::size_t real_index = (front_ + human_index) % mem_.capacity_;
    for (const T& element : data) {
        mem_.data_[real_index] = element;
        real_index = (real_index + 1) % mem_.capacity_;
    }
    mem_.size_ += data.size();
}

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& other) {
    if (this == &other) {
        return *this;
    }
    front_ = other.front_;
    back_ = other.back_;
    mem_.SetMemory(other.mem_.size_);
    mem_.size_ = other.mem_.size_;
    mem_.capacity_ = other.mem_.capacity_;
    for (std::size_t i = 0; i < mem_.size_; ++i) {
        mem_.data_[i] = other.mem_.data_[i];
    }
    return *this;
}

template <typename T>
Vector<T>& Vector<T>::operator=(Vector<T>&& other) {
    if (this == &other) {
        return *this;
    }
    mem_.SetMemory(other.mem_.size_);
    mem_.size_ = other.mem_.size_;
    mem_.capacity_ = other.mem_.capacity_;
    front_ = 0;
    back_ = mem_.size_ == 0 ? 0 : mem_.size_ - 1;

    std::size_t old_index = other.front_;
    for (std::size_t i = 0; i < mem_.size_; ++i) {
        mem_.data_[i] = other.mem_.data_[old_index++];
        if (old_index == other.mem_.capacity_) {
            old_index = 0;
        }
    }
    other.mem_.size_ = 0;
    other.mem_.capacity_ = 0;
    other.mem_.data_ = nullptr;
    return *this;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const Vector<T>& vec) {
    if (vec.mem_.size() == 0) {
        os << "{ }";
        return os;
    }
    os << "{ ";
    for (std::size_t i = 0; i + 1 < vec.mem_.size(); ++i) {
        os << vec[i] << ", ";
    }
    os << vec[vec.mem_.size() - 1] << " }";
    return os;
}

template <typename T>
std::istream& operator>>(std::istream& is, Vector<T>& vec) {
    std::size_t new_size = 0;
    is >> new_size;
    vec.ResetMemory(new_size);
    for (std::size_t i = 0; i < vec.mem_.size(); ++i) {
        is >> vec[i];
    }
    return is;
}

template <typename T>
const T& Vector<T>::operator[](std::size_t human_index) const noexcept {
    std::size_t real_index = (front_ + human_index) % mem_.capacity_;
    return mem_.data_[real_index];
}

template <typename T>
T& Vector<T>::operator[](std::size_t human_index) noexcept {
    std::size_t real_index = (front_ + human_index) % mem_.capacity_;
    return mem_.data_[real_index];
}

template <typename T>
void Vector<T>::PushElementsToInsert(std::size_t human_index,
                                     Direction direction, std::size_t count) {
    std::size_t real_index = (front_ + human_index) % mem_.capacity_;
    std::size_t real_new_index;

    if (direction == Direction::kLeft) {
        for (std::size_t i = front_; i != (real_index + 1) % mem_.capacity_;
             i = (i + 1) % mem_.capacity_) {
            real_new_index = (i - count + mem_.capacity_) % mem_.capacity_;
            mem_.data_[real_new_index] = mem_.data_[i];
        }
        front_ = (front_ - count + mem_.capacity_) % mem_.capacity_;
        return;
    }
    if (direction == Direction::kRight) {
        std::size_t end_index =
            (real_index == 0) ? mem_.capacity_ - 1 : real_index - 1;
        for (std::size_t i = (back_ + count) % mem_.capacity_; i != end_index;
             i = (i - 1 + mem_.capacity_) % mem_.capacity_) {
            real_new_index = (i - count + mem_.capacity_) % mem_.capacity_;
            mem_.data_[i] = mem_.data_[real_new_index];
        }
        back_ = (back_ + count) % mem_.capacity_;
        return;
    }
}

template <typename T>
void Vector<T>::PushElementsToErase(std::size_t human_index,
                                    Direction direction, std::size_t count) {
    std::size_t left_count = human_index;
    std::size_t right_count = mem_.size_ - human_index - count;

    if (direction == Direction::kLeft) {
        std::size_t copy_start_index =
            (front_ + human_index + count) % mem_.capacity_;
        std::size_t remove_start_index =
            (front_ + human_index) % mem_.capacity_;
        for (std::size_t i = 0; i < right_count; ++i) {
            std::size_t copy_index = (copy_start_index + i) % mem_.capacity_;
            std::size_t remove_index =
                (remove_start_index + i) % mem_.capacity_;
            mem_.data_[remove_index] = mem_.data_[copy_index];
        }
        back_ = (back_ - count + mem_.capacity_) % mem_.capacity_;
        return;
    }
    if (direction == Direction::kRight) {
        for (std::size_t i = left_count; i > 0; --i) {
            std::size_t copy_index = (front_ + i - 1) % mem_.capacity_;
            std::size_t remove_index =
                (front_ + i - 1 + count) % mem_.capacity_;
            mem_.data_[remove_index] = mem_.data_[copy_index];
        }
        front_ = (front_ + count) % mem_.capacity_;
        return;
    }
}

template <typename T>
void Vector<T>::ResetMemory(std::size_t new_size) {
    mem_.ResetMemory(new_size, front_);
    front_ = 0;
    back_ = mem_.size_ == 0 ? 0 : mem_.size_ - 1;
}

template <typename T>
void Vector<T>::Clear() {
    mem_.ClearMemory();
    front_ = 0;
    back_ = 0;
}

template <typename T>
void Vector<T>::Shuffle() noexcept {
    if (mem_.size_ <= 1) {
        return;
    }
    static std::random_device rd;
    static std::mt19937 gen(rd());
    for (std::size_t i = mem_.size_ - 1; i > 0; --i) {
        std::uniform_int_distribution<std::size_t> dist(0, i);
        std::size_t j = dist(gen);
        T tmp = (*this)[i];
        (*this)[i] = (*this)[j];
        (*this)[j] = tmp;
    }
}

template <typename T>
void Vector<T>::SelectionSort() noexcept {
    if (mem_.size_ <= 1) {
        return;
    }
    for (std::size_t i = 0; i + 1 < mem_.size_; ++i) {
        std::size_t min_index = i;
        for (std::size_t j = i + 1; j < mem_.size_; ++j) {
            if ((*this)[j] < (*this)[min_index]) {
                min_index = j;
            }
        }
        if (min_index != i) {
            T tmp = (*this)[i];
            (*this)[i] = (*this)[min_index];
            (*this)[min_index] = tmp;
        }
    }
}

}  // namespace vector_lib

#endif  // LIB_VECTOR_TVECTOR_H_
