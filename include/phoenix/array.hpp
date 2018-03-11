#ifndef PHOSTDLIB_ARRAY_HPP
#define PHOSTDLIB_ARRAY_HPP
#include <array>
#include <exception>
#include <initializer_list>
#ifndef PHOSTDLIB_DONT_SUPPORT_PRINT
#include <iostream>
#endif

namespace phoenix {
template <typename T, std::size_t N>
class array {
 public:
// proper constexpr support since C++14 standard
#if __cplusplus >= 201402L
  constexpr array() : _data{} {}

  constexpr explicit array(T value) {
    for (auto* x = _data; x != _data + N; ++x) *x = value;
  }

  constexpr explicit array(const std::initializer_list<T>& init_list) : _data{} {
    if (init_list.size() > N)
      throw std::out_of_range("Initializer list too large!");

    auto* i = _data;
    for (const auto& x : init_list) {
      *(i++) = x;
    }
  }

  constexpr array(const array<T, N>& other) : _data{} {
    auto* i = _data;
    for (const auto& x : other) *(i++) = x;
  }

  constexpr array<T, N>& operator=(const array<T, N>& other) {
    auto* i = _data;
    for (const auto& x : other) *(i++) = x;
  }

  constexpr explicit array(const std::array<T, N>& other) : _data{} {
    auto* i = _data;
    for (const auto& x : other) *(i++) = x;
  }
#else
  array() : _data{} {}

  explicit array(T value) {
    for (auto* x = _data; x != _data + N; ++x) *x = value;
  }

  explicit array(const std::initializer_list<T>& init_list) : _data{} {
    if (init_list.size() > N)
      throw std::out_of_range("Initializer list too large!");

    auto* i = _data;
    for (const auto& x : init_list) {
      *(i++) = x;
    }
  }

  explicit array(const array<T, N>& other) : _data{} {
    auto* i = _data;
    for (const auto& x : other) *(i++) = x;
  }

  array<T, N>& operator=(const array<T, N>& other) {
    auto* i = _data;
    for (const auto& x : other) *(i++) = x;
    return *this;
  }

  explicit array(const std::array<T, N>& other) : _data{} {
    auto* i = _data;
    for (const auto& x : other) *(i++) = x;
  }
#endif

  T* begin() { return _data; }
  T* end() { return _data + N; }
  const T* begin() const { return _data; }
  const T* end() const { return _data + N; }

  // Compatibility purposes
  const T* cbegin() const { return _data; }
  const T* cend() const { return _data + N; }

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
    auto* it = vec.cbegin();
    for (; it != vec.cend() - 1; it++) os << *it << ", ";
    return os << *(++it) << '}';
  }
  #endif

 private:
  T _data[N];
};
}  // namespace phoenix

#endif
