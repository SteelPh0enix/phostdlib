#ifndef PHOSTDLIB_SORT_HPP
#define PHOSTDLIB_SORT_HPP
#include "utility.hpp"
#include <chrono>
#include <random>

namespace phoenix {

  template<typename BidirectionalIterator,
           typename Compare = decltype(is_greater<typename BidirectionalIterator::const_reference>)>
  void insertion_sort(BidirectionalIterator begin, BidirectionalIterator end,
                      Compare compare = is_greater) {
    for(auto i = begin + 1; i != end; i++) {
      for(auto j = i; j != begin && compare(*(j - 1), *j); j--) {
        swap(*j, *(j - 1));
      }
    }
  }

  template<typename BidirectionalIterator,
           typename Compare = decltype(is_greater<typename BidirectionalIterator::const_reference>)>
  void bubble_sort(BidirectionalIterator begin, BidirectionalIterator end,
                   Compare compare = is_greater) {
    for(auto i = begin + 1; i != end; i++) {
      for(auto j = end - 1; j != i - 1; j--) {
        if(compare(*(j - 1), *j))
          swap(*j, *(j - 1));
      }
    }
  }

  template<typename BidirectionalIterator,
           typename Compare = decltype(is_greater<typename BidirectionalIterator::const_reference>)>
  void selection_sort(BidirectionalIterator begin, BidirectionalIterator end,
                      Compare compare = is_greater) {
    for(auto i = begin; i != end; i++) {
      auto minimal = i;
      for(auto j = i + 1; j != end; j++) {
        if (compare(*minimal, *j)) {
          minimal = j;
        }
      }

      if (minimal != i) {
        swap(*i, *minimal);
      }
    }
  }

  template<typename RandomAccessIterator,
      typename Compare = decltype(is_greater<typename RandomAccessIterator::const_reference>)>
  void bogo_sort(RandomAccessIterator begin,
                 typename RandomAccessIterator::size_type length,
                 Compare compare = is_greater) {
    std::mt19937 gen(
        static_cast<std::mt19937::result_type>(std::chrono::system_clock::now().time_since_epoch().count()));
    std::uniform_int_distribution<typename RandomAccessIterator::size_type> dist(0, length - 1);

    auto bogo = [&]() {
      for (typename RandomAccessIterator::size_type i{}; i < length; i++) {
        swap(*(begin + dist(gen)), *(begin + dist(gen)));
      }
    };

    // ¯\_(ツ)_/¯
    while (!is_sorted(begin, RandomAccessIterator(begin + length), compare)) {
      bogo();
    }
  }

}

#endif //PHOSTDLIB_SORT_HPP
