#ifndef PHOSTDLIB_ITERATOR_HPP
#define PHOSTDLIB_ITERATOR_HPP
#include <type_traits>

namespace phoenix {
  enum class iterator_flag : unsigned {
    input = 0x01,
    output = 0x02,
    forward = 0x04 | input,
    bidirectional = 0x08 | forward,
    random_access = 0x16 | bidirectional
  };

  iterator_flag operator|(const iterator_flag& first, const iterator_flag& second) {
    return static_cast<iterator_flag>(static_cast<unsigned>(first) | static_cast<unsigned>(second));
  }

  iterator_flag operator&(const iterator_flag& first, const iterator_flag& second) {
    return static_cast<iterator_flag>(static_cast<unsigned>(first) & static_cast<unsigned>(second));
  }

  iterator_flag operator^(const iterator_flag& first, const iterator_flag& second) {
    return static_cast<iterator_flag>(static_cast<unsigned>(first) ^ static_cast<unsigned>(second));
  }

  iterator_flag operator~(const iterator_flag& it) {
    return static_cast<iterator_flag>(~static_cast<unsigned>(it));
  }

  iterator_flag& operator|=(iterator_flag& first, const iterator_flag& second) {
    return first = first | second;
  }

  iterator_flag& operator&=(iterator_flag& first, const iterator_flag& second) {
    return first = first & second;
  }

  iterator_flag& operator^=(iterator_flag& first, const iterator_flag& second) {
    return first = first ^ second;
  }
}

#endif //PHOSTDLIB_ITERATOR_HPP
