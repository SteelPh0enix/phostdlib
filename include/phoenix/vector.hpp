#ifndef PHOSTDLIB_VECTOR_HPP
#define PHOSTDLIB_VECTOR_HPP
#include <exception>
#include <initializer_list>
#include <vector>
#include <phoenix/iterator_flag.hpp>
#ifndef PHOSTDLIB_DONT_SUPPORT_PRINT
#include <iostream>
#endif

namespace phoenix {
// AllocSize is capacity added to vector when reallocating at push()
template <typename T, std::size_t AllocSize = 16>
class vector {
public:

  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using pointer = T*;
  using const_pointer = const T*;
  using difference_type = std::ptrdiff_t;
  using size_type = std::size_t;

  class iterator {
  public:
    using self = iterator;
    static constexpr auto iterator_type = iterator_flag::random_access;

    using value_type = value_type;
    using reference = reference;
    using const_reference = const T&;
    using pointer = pointer;
    using const_pointer = const T*;
    using difference_type = std::ptrdiff_t;
    using size_type = std::size_t;

    explicit iterator(pointer e) : _ptr{e} {}

    self& operator++() {
      _ptr++;
      return *this;
    }

    self operator++(int) {
      auto t = *this;
      this->operator++();
      return t;
    }

    self& operator--() {
      _ptr--;
      return *this;
    }

    self operator--(int) {
      auto t = *this;
      this->operator--();
      return t;
    }

    reference operator*() {
      return *_ptr;
    }

    pointer operator->() {
      return _ptr;
    }

    bool operator==(const self& other) const {
      return _ptr == other._ptr;
    }

    bool operator!=(const self& other) const {
      return _ptr != other._ptr;
    }

    self operator+(difference_type x) {
      return self(_ptr + x);
    }

    self operator-(difference_type x) {
      return self(_ptr - x);
    }

    self& operator+=(difference_type x) {
      _ptr += x;
      return *this;
    }

    self& operator-=(difference_type x) {
      _ptr -= x;
      return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const iterator& it) {
      return os << it._ptr;
    }

  private:
    pointer _ptr;
  };

  class const_iterator {
  public:
    using self = const_iterator;
    static constexpr auto iterator_type = iterator_flag::random_access;

    using value_type = value_type;
    using const_reference = const_reference;
    using const_pointer = const_pointer;
    using difference_type = std::ptrdiff_t;
    using size_type = std::size_t;

    explicit const_iterator(const_pointer e) : _ptr{e} {}

    self& operator++() {
      _ptr++;
      return *this;
    }

    self operator++(int) {
      auto t = *this;
      this->operator++();
      return t;
    }

    self& operator--() {
      _ptr--;
      return *this;
    }

    self operator--(int) {
      auto t = *this;
      this->operator--();
      return t;
    }

    const_reference operator*() const {
      return *_ptr;
    }

    const_pointer operator->() const {
      return _ptr;
    }

    bool operator==(const self& other) const {
      return _ptr == other._ptr;
    }

    bool operator!=(const self& other) const {
      return _ptr != other._ptr;
    }

    self operator+(difference_type x) {
      return self(_ptr + x);
    }

    self operator-(difference_type x) {
      return self(_ptr - x);
    }

    self& operator+=(difference_type x) {
      _ptr += x;
      return *this;
    }

    self& operator-=(difference_type x) {
      _ptr -= x;
      return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const const_iterator& it) {
      return os << it._ptr;
    }

  private:
    const_pointer _ptr;
  };

  // Constructors
  vector() : _data{nullptr}, _size{0u}, _capacity{0u} {}

  explicit vector(size_type size)
      : _data{new T[size]}, _size{size}, _capacity{size} {
    for (auto* x = _data; x != _data + _size; ++x) {
      *x = value_type{};
    }
  }

  vector(size_type size, const_reference value)
      : _data{new T[size]}, _size{size}, _capacity{size} {
    for (auto* x = _data; x != _data + _size; ++x) {
      *x = value;
    }
  }

  vector(const std::initializer_list<value_type>& data)
      : _data{new T[data.size()]}, _size{data.size()}, _capacity{data.size()} {
    auto* i = _data;
    for (const auto &e : data) {
      *(i++) = e;
    }
  }

  explicit vector(const std::vector<value_type>& data)
      : _data{new T[data.size()]}, _size{data.size()}, _capacity{data.size()} {
    auto* i = _data;
    for (const auto &e : data) {
      *(i++) = e;
    }
  }

  // Rule of five
  vector(const vector<value_type, AllocSize>& other)
      : _data{new T[other._size]}, _size{other._size}, _capacity{other._size} {
    auto* i = _data;
    for (auto* j = other._data; j != other._data + other._size; j++) {
      *(i++) = *j;
    }
  }

  vector(vector<value_type, AllocSize>&& other) noexcept
      : _data{other._data}, _size{other._size}, _capacity{other._capacity} {
    other._data = nullptr;
    other._size = 0;
    other._capacity = 0;
  }

  vector<value_type, AllocSize>& operator=(const vector<value_type, AllocSize>& other) {
    reserve(other._size);
    auto* i = begin();
    for (const auto &x : other) {
      *(i++) = x;
    }
    return *this;
  }

  vector<value_type, AllocSize>& operator=(vector<value_type, AllocSize>&& other) noexcept {
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
  reference operator[](size_type i) { return _data[i]; }
  const_reference operator[](size_type i) const { return _data[i]; }

  // Guarded access
  reference at(size_type i) {
    if (i >= _size)
      throw std::out_of_range("Vector index out of bounds!");
    return _data[i];
  }

  const_reference at(size_type i) const {
    if (i >= _size)
      throw std::out_of_range("Vector index out of bounds!");
    return _data[i];
  }

  // Iterators support (basic)
  iterator begin() { return iterator(_data); }
  iterator end() { return iterator(_data + _size); }
  const_iterator begin() const { return const_iterator(_data); }
  const_iterator end() const { return const_iterator(_data + _size); }

  // Compatibility purposes
  const_iterator cbegin() const { return const_iterator(_data); }
  const_iterator cend() const { return const_iterator(_data + _size); }

  // Adding and removing elements
  void push(const_reference value) {
    // Check if capacity is enought, if now - reserve more
    if (_size == _capacity)
      reserve(_capacity + AllocSize);
    _data[_size++] = value;
  }

  value_type pop() {
    if (_size == 0) {
      throw std::out_of_range("Cannot pop from an empty vector!");
    }
    return _data[--_size];
  }

  // Utility
  size_type size() const { return _size; }
  size_type capacity() const { return _capacity; }

  // Only access directly to raw data provided is const access
  const_pointer data() const { return _data; }

  void reserve(size_type new_size) {
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

  void resize(size_type new_size) {
    reserve(new_size);
    _size = new_size;
  }

  #ifndef PHOSTDLIB_DONT_SUPPORT_PRINT
  std::ostream& print(std::ostream& os, const char* separator = ", ") const {
    for (auto i = cbegin(); i != cend(); i++)
      os << *i << separator;
    return os;
  }

  friend std::ostream& operator<<(std::ostream& os, const vector<value_type, AllocSize> &vec) {
    os << '{';
    auto it = vec.cbegin();
    for (; it != vec.cend() - 1; it++)
      os << *it << ", ";
    return os << *(++it) << '}';
  }
  #endif

private:
  pointer _data;
  size_type _size, _capacity;
};
} // namespace phoenix

#endif
