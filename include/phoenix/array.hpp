#ifndef PHOSTDLIB_ARRAY_HPP
#define PHOSTDLIB_ARRAY_HPP
#include <array>
#include <exception>
#include <initializer_list>
#include <phoenix/iterator_flag.hpp>
#ifndef PHOSTDLIB_DONT_SUPPORT_PRINT
#include <iostream>
#endif

namespace phoenix {
  template <typename T, std::size_t N>
  class array {
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

    using iterator = iterator;
    using const_iterator = const_iterator;

    // proper constexpr support since C++14 standard
    #if __cplusplus >= 201402L
    constexpr array() : _data{} {}

    constexpr explicit array(T value) {
      for (auto* x = _data; x != _data + N; ++x) *x = value;
    }

    constexpr array(const std::initializer_list<T>& init_list) : _data{} {
      if (init_list.size() > N)
        throw std::out_of_range("Initializer list too large!");

      auto* i = _data;
      for (const auto& x : init_list) {
        *(i++) = x;
      }
    }

    #else
    array() : _data{} {}

    explicit array(T value) {
      for (auto* x = _data; x != _data + N; ++x) *x = value;
    }

    array(const std::initializer_list<T>& init_list) : _data{} {
      if (init_list.size() > N)
        throw std::out_of_range("Initializer list too large!");

      auto* i = _data;
      for (const auto& x : init_list) {
        *(i++) = x;
      }
    }
    #endif

    array(const array<T, N>& other) : _data{} {
      auto* i = _data;
      for (const auto& x : other) *(i++) = x;
    }

    explicit array(const std::array<T, N>& other) : _data{} {
      auto* i = _data;
      for (const auto& x : other) *(i++) = x;
    }

    array<T, N>& operator=(const array<T, N>& other) {
      auto* i = _data;
      for (const auto& x : other) *(i++) = x;
      return *this;
    }

    iterator begin() { return iterator(_data); }
    iterator end() { return iterator(_data + N); }
    const_iterator begin() const { return const_iterator(_data); }
    const_iterator end() const { return const_iterator(_data + N); }

    // This is probably just a workaround for const-compatibility
    const_iterator cbegin() const { return const_iterator(_data); }
    const_iterator cend() const { return const_iterator(_data + N); }

    T& operator[](std::size_t i) { return _data[i]; }
    const T& operator[](std::size_t i) const { return _data[i]; }

    T& at(std::size_t i) {
      if (i >= N) throw std::out_of_range("Array index out of bounds!");
      return _data[i];
    }
    const T& at(std::size_t i) const {
      if (i >= N) throw std::out_of_range("Array index out of bounds!");
      return _data[i];
    }

    std::size_t size() const { return N; }

    #ifndef PHOSTDLIB_DONT_SUPPORT_PRINT
    std::ostream& print(std::ostream& os, const char* separator = ", ") const {
      for (T* i = _data; i != _data + N; i++) os << *i << separator;
      return os;
    }

    friend std::ostream& operator<<(std::ostream& os, const array<T, N>& vec) {
      os << '{';
      auto it = vec.cbegin();
      for (; it != vec.cend() - 1; it++) os << *it << ", ";
      return os << *(++it) << '}';
    }
    #endif

   private:
    T _data[N];
  };
}  // namespace phoenix

#endif
