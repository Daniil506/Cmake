#ifndef LIB_VECTOR_MEM_DATA_H_
#define LIB_VECTOR_MEM_DATA_H_

#include <cstddef>
#include <initializer_list>

namespace vector_lib {

    constexpr std::size_t kMemStep = 15;

    inline std::size_t CalculateCapacity(std::size_t size) {
        return size == 0
            ? kMemStep
            : (size - 1) / kMemStep * kMemStep + kMemStep;
    }

    template <typename T>
    class Vector;

    template <typename T>
    class MemData {
    public:
        explicit MemData(std::size_t size = 0);
        MemData(std::initializer_list<T> data);
        MemData(T* data, std::size_t size);
        MemData(const MemData& other);
        MemData(MemData&& other);
        ~MemData();

        bool IsEmpty() const noexcept;
        bool IsFull() const noexcept;

        std::size_t Size() const noexcept;
        std::size_t Capacity() const noexcept;
        const T* Data() const noexcept;

        void SetMemory(std::size_t size) noexcept;
        void ResetMemory(std::size_t size,
            std::size_t start_index = 0) noexcept;
        void ClearMemory() noexcept;

        MemData& operator=(const MemData& other) noexcept;
        MemData& operator=(MemData&& other) noexcept;

        friend class Vector<T>;

    private:
        std::size_t size_;
        std::size_t capacity_;
        T* data_;
    };

    template <typename T>
    bool MemData<T>::IsEmpty() const noexcept {
        return size_ == 0;
    }

    template <typename T>
    bool MemData<T>::IsFull() const noexcept {
        return size_ == capacity_;
    }

    template <typename T>
    std::size_t MemData<T>::Size() const noexcept {
        return size_;
    }

    template <typename T>
    std::size_t MemData<T>::Capacity() const noexcept {
        return capacity_;
    }

    template <typename T>
    const T* MemData<T>::Data() const noexcept {
        return data_;
    }

    template <typename T>
    MemData<T>::MemData(std::size_t size)
        : size_(0),
        capacity_(CalculateCapacity(size)),
        data_(capacity_ == 0 ? nullptr : new T[capacity_]) {
    }

    template <typename T>
    MemData<T>::MemData(std::initializer_list<T> data)
        : size_(data.size()),
        capacity_(CalculateCapacity(size_)),
        data_(capacity_ == 0 ? nullptr : new T[capacity_]) {
        std::size_t i = 0;
        for (const T& element : data) {
            data_[i++] = element;
        }
    }

    template <typename T>
    MemData<T>::MemData(T* data, std::size_t size)
        : size_(size),
        capacity_(CalculateCapacity(size_)),
        data_(capacity_ == 0 ? nullptr : new T[capacity_]) {
        for (std::size_t i = 0; i < size_; ++i) {
            data_[i] = data[i];
        }
    }

    template <typename T>
    MemData<T>::MemData(const MemData& other)
        : size_(other.size_),
        capacity_(other.capacity_),
        data_(capacity_ == 0 ? nullptr : new T[capacity_]) {
        for (std::size_t i = 0; i < size_; ++i) {
            data_[i] = other.data_[i];
        }
    }

    template <typename T>
    MemData<T>::MemData(MemData&& other)
        : size_(other.size_),
        capacity_(other.capacity_),
        data_(other.data_) {
        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = kMemStep;
    }

    template <typename T>
    MemData<T>::~MemData() {
        delete[] data_;
    }

    template <typename T>
    void MemData<T>::SetMemory(std::size_t size) noexcept {
        if (capacity_ == CalculateCapacity(size)) {
            size_ = 0;
            return;
        }
        delete[] data_;
        size_ = 0;
        capacity_ = CalculateCapacity(size);
        data_ = capacity_ == 0 ? nullptr : new T[capacity_];
    }

    template <typename T>
    void MemData<T>::ResetMemory(std::size_t size,
        std::size_t start_index) noexcept {
        if (capacity_ == CalculateCapacity(size)) {
            return;
        }
        std::size_t new_capacity = CalculateCapacity(size);
        T* new_data = new_capacity == 0 ? nullptr : new T[new_capacity];

        std::size_t copy_count = size_ <= size ? size_ : size;
        for (std::size_t i = 0; i < copy_count; ++i) {
            new_data[i] = data_[start_index++];
            if (start_index >= capacity_) {
                start_index = 0;
            }
        }

        capacity_ = new_capacity;
        delete[] data_;
        data_ = new_data;
    }

    template <typename T>
    void MemData<T>::ClearMemory() noexcept {
        delete[] data_;
        data_ = new T[kMemStep];
        size_ = 0;
        capacity_ = kMemStep;
    }

    template <typename T>
    MemData<T>& MemData<T>::operator=(const MemData<T>& other) noexcept {
        if (&other == this) {
            return *this;
        }
        delete[] data_;
        size_ = other.size_;
        capacity_ = other.capacity_;
        data_ = capacity_ == 0 ? nullptr : new T[capacity_];
        for (std::size_t i = 0; i < size_; ++i) {
            data_[i] = other.data_[i];
        }
        return *this;
    }

    template <typename T>
    MemData<T>& MemData<T>::operator=(MemData<T>&& other) noexcept {
        if (&other == this) {
            return *this;
        }
        delete[] data_;
        size_ = other.size_;
        capacity_ = other.capacity_;
        data_ = other.data_;
        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = kMemStep;
        return *this;
    }

}  

#endif  