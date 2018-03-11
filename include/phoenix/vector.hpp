#ifndef PHOSTDLIB_VECTOR_HPP
#define PHOSTDLIB_VECTOR_HPP
#include <exception>
#include <initializer_list>
#ifndef PHOSTDLIB_DONT_SUPPORT_PRINT
#include <iostream>
#endif
#include <vector>

namespace phoenix {
// AllocSize is capacity added to vector when reallocating at push()
template <typename T, std::size_t AllocSize = 16>
class vector {
public:
  // Constructors
  vector() : _data{nullptr}, _size{0u}, _capacity{0u} {}

  explicit vector(std::size_t size)
      : _data{new T[size]}, _size{size}, _capacity{size} {
    for (auto* x = _data; x != _data + _size; ++x) {
      *x = T{};
    }
  }

  vector(std::size_t size, const T& value)
      : _data{new T[size]}, _size{size}, _capacity{size} {
    for (auto* x = _data; x != _data + _size; ++x) {
      *x = value;
    }
  }

  vector(const std::initializer_list<T>& data)
      : _data{new T[data.size()]}, _size{data.size()}, _capacity{data.size()} {
    auto* i = _data;
    for (const auto &e : data) {
      *(i++) = e;
    }
  }

  explicit vector(const std::vector<T>& data)
      : _data{new T[data.size()]}, _size{data.size()}, _capacity{data.size()} {
    auto* i = _data;
    for (const auto &e : data) {
      *(i++) = e;
    }
  }

  // Rule of five
  vector(const vector<T, AllocSize>& other)
      : _data{new T[other._size]}, _size{other._size}, _capacity{other._size} {
    auto* i = _data;
    for (auto* j = other._data; j != other._data + other._size; j++) {
      *(i++) = *j;
    }
  }

  vector(vector<T, AllocSize>&& other) noexcept
      : _data{other._data}, _size{other._size}, _capacity{other._capacity} {
    other._data = nullptr;
    other._size = 0;
    other._capacity = 0;
  }

  vector<T, AllocSize>& operator=(const vector<T, AllocSize>& other) {
    reserve(other._size);
    auto* i = begin();
    for (const auto &x : other) {
      *(i++) = x;
    }
    return *this;
  }

  vector<T, AllocSize>& operator=(vector<T, AllocSize>&& other) {
    _data = other._data;
    _size = other._size;
    _capacity = other._capacity;

    other._data = nullptr;
    other._size = 0;
    other._capacity = 0;
    return *this;
  }

  // Destructor
  ~vector() { delete[] _data; }

  // Raw access
  T& operator[](std::size_t i) { return _data[i]; }
  const T& operator[](std::size_t i) const { return _data[i]; }

  // Guarded access
  T& at(std::size_t i) {
    if (i >= _size)
      throw std::out_of_range("Vector index out of bounds!");
    return _data[i];
  }

  const T& at(std::size_t i) const {
    if (i >= _size)
      throw std::out_of_range("Vector index out of bounds!");
    return _data[i];
  }

  // Iterators support (basic)
  T* begin() { return _data; }
  T* end() { return _data + _size; }
  const T* begin() const { return _data; }
  const T* end() const { return _data + _size; }

  // Compatibility purposes
  const T* cbegin() const { return _data; }
  const T* cend() const { return _data + _size; }

  // Adding and removing elements
  void push(const T &value) {
    // Check if capacity is enought, if now - reserve more
    if (_size == _capacity)
      reserve(_capacity + AllocSize);
    _data[_size++] = value;
  }

  T pop() {
    if (_size == 0) {
      throw std::out_of_range("Cannot pop from an empty vector!");
    }
    return _data[--_size];
  }

  // Utility
  std::size_t size() const { return _size; }
  std::size_t capacity() const { return _capacity; }

  // Only access directly to raw data provided is const access
  const T* data() const { return _data; }

  void reserve(std::size_t new_size) {
    // In case when actual capacity is greater or equal
    if (_size >= new_size)
      return;

    // Allocate new block
    auto* new_data = new T[new_size];

    // Copy the data to new block
    auto* new_data_it = new_data;
    for (auto* x = _data; x != (_data + _size); ++x) {
      *(new_data_it++) = *x;
    }

    // Deallocate old block, set new as default one, increase capacity
    delete[] _data;
    _data = new_data;
    _capacity = new_size;
  }

  void resize(std::size_t new_size) {
    reserve(new_size);
    _size = new_size;
  }

  #ifndef PHOSTDLIB_DONT_SUPPORT_PRINT
  std::ostream& print(std::ostream& os, const char* separator = ", ") const {
    for (T* i = _data; i != _data + _size; i++)
      os << *i << separator;
    return os;
  }

  friend std::ostream& operator<<(std::ostream& os, const vector<T, AllocSize> &vec) {
    os << '{';
    auto* it = vec.cbegin();
    for (; it != vec.cend() - 1; it++)
      os << *it << ", ";
    return os << *(++it) << '}';
  }
  #endif

private:
  T* _data;
  std::size_t _size, _capacity;
};
} // namespace phoenix

#endif
