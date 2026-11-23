#include <stdexcept>
#include <cstddef>

template<typename T>
class StackOnMass {
    T* _data;
    size_t _size;
    int _top;

public:
    explicit StackOnMass(size_t size);
    StackOnMass(const StackOnMass& other);
    size_t get_size();
    int get_top();
    ~StackOnMass();

    void push(const T& num);
    void push_with_eviction(const T& num);

    inline T pop();
    inline T& top();
    inline bool is_empty() const noexcept;
    inline bool is_full() const noexcept;
};

template<typename T>
StackOnMass<T>::StackOnMass(size_t size) : _size(size), _top(-1) {
    _data = new T[_size];
}

template<typename T>
StackOnMass<T>::StackOnMass(const StackOnMass& other)
    : _size(other._size), _top(other._top) {
    _data = new T[_size];

    for (int i = 0; i <= _top; i++) {
        _data[i] = other._data[i];
    }
}

template<typename T>
size_t StackOnMass<T>::get_size() {
    return _size;
}

template<typename T>
int StackOnMass<T>::get_top() {
    return _top;
}

template<typename T>
StackOnMass<T>::~StackOnMass() {
    delete[] _data;
}

template<typename T>
void StackOnMass<T>::push(const T& num) {
    if (is_full()) {
        throw std::out_of_range("StackOnMass::push(): stack is full");
    }
    else {
        _data[++_top] = num;
    }
}

// §®§Ö§ä§à§Õ §Ó§í§ä§Ö§ã§ß§Ö§ß§Ú§ñ
template<typename T>
void StackOnMass<T>::push_with_eviction(const T& num) {
    if (_size == 0) {
        throw std::out_of_range("StackOnMass::push_with_eviction(): stack is empty");
    }

    T value = num;

    if (is_full()) {
        for (size_t i = 0; i < _size - 1; i++) {
            _data[i] = _data[i + 1];
        }

        _data[_size - 1] = value;
    }
    else {
        _data[++_top] = value;
    }
}

template<typename T>
inline T StackOnMass<T>::pop() {
    if (is_empty()) {
        throw std::out_of_range("StackOnMass::pop(): stack is empty");
    }
    else {
        return _data[_top--];
    }
}

template<typename T>
inline T& StackOnMass<T>::top() {
    if (is_empty()) {
        throw std::out_of_range("StackOnMass::top(): stack is empty");
    }
    else {
        return _data[_top];
    }
}

template<typename T>
inline bool StackOnMass<T>::is_empty() const noexcept {
    return _top == -1;
}

template<typename T>
inline bool StackOnMass<T>::is_full() const noexcept {
    return _size == 0 || static_cast<size_t>(_top + 1) >= _size;
}