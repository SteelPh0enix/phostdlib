#ifndef PHOSTDLIB_UTILITY_HPP
#define PHOSTDLIB_UTILITY_HPP
#ifndef PHOSTDLIB_DONT_SUPPORT_PRINT
#include <iostream>
#endif

namespace phoenix {
  template <typename T1, typename T2>
  struct pair {
    T1 first;
    T2 second;

    #ifndef PHOSTDLIB_DONT_SUPPORT_PRINT
    friend std::ostream& operator<<(std::ostream& os, const phoenix::pair<T1, T2>& p) {
      return os << "{" << p.first << ", " << p.second << "}";
    }
    #endif
  };

  template <typename T>
  T greater(const T& first, const T& second) {
    return first > second ? first : second;
  }

  template <typename T>
  T lesser(const T& first, const T& second) {
    return first < second ? first : second;
  }

  template <typename T>
  bool is_greater(const T& first, const T& second) {
    return first > second;
  }

  template <typename T>
  bool is_greater_or_equal(const T& first, const T& second) {
    return first >= second;
  }

  template <typename T>
  bool is_lesser(const T& first, const T& second) {
    return first < second;
  }

  template <typename T>
  bool is_lesser_or_equal(const T& first, const T& second) {
    return first <= second;
  }

  template <typename T>
  bool is_equal(const T& first, const T& second) {
    return first == second;
  }

  template <typename T>
  bool is_not_equal(const T& first, const T& second) {
    return first != second;
  }

  template <typename T>
  void swap(T& first, T& second) {
    T temporary = first;
    first = second;
    second = temporary;
  }

  //TODO: Maybe use std::enable_if? Or some metaprogramming?
  template <typename ConstIterator, typename Compare = decltype(is_greater<typename ConstIterator::const_reference>)>
  bool is_sorted(ConstIterator begin, ConstIterator end, Compare compare = is_greater) {
    for(auto it = begin; it + 1 != end; ++it) {
      if (compare(*(it), *(it + 1))) {
        return false;
      }
    }
    return true;
  }
}

#endif //PHOSTDLIB_UTILITY_HPP
