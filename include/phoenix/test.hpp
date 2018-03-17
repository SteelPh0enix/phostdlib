#ifndef PHOSTDLIB_TEST_HPP
#define PHOSTDLIB_TEST_HPP
#include <exception>
#include <sstream>
#include <iostream>

namespace phoenix {
  class test_exception : public std::exception {
   public:
    test_exception(const std::string& message) : _message{message} {}
    // what a monster
    virtual const char* what() const noexcept override {
      return _message.c_str();
    }

   private:
    std::string _message;
  };
  template<typename F, typename OutputStream = std::ostream>
  void run_test(F test_function, const std::string& test_name, OutputStream& output = std::cout) {
    try {
      test_function();
    } catch (const test_exception &e) {
      output << '<' << test_name << "> " <<  e.what() << std::endl;
    } catch (const std::exception &e) {
      output << '<' << test_name << "> Non-test exception occurred: " << e.what() << std::endl;
    }

    output << test_name << " test passed!" << std::endl;
  }

class test {
 public:
  template <typename T1, typename T2>
  static void eq(const T1& first, const T2& second,
                 const std::string& message = std::string{}) {
    if (first != second) {
      std::stringstream exmsg_stream;
      exmsg_stream << "<test::eq failed!> " << message << " [first: " << first
                   << "] [second: " << second << "]";
      throw test_exception(exmsg_stream.str());
    }
  }

  template <typename T1, typename T2>
  static void neq(const T1& first, const T2& second,
                  const std::string& message = std::string{}) {
    if (first == second) {
      std::stringstream exmsg_stream;
      exmsg_stream << "<test::neq failed!> " << message << " [first: " << first
                   << "] [second: " << second << "]";
      throw test_exception(exmsg_stream.str());
    }
  }

  template <typename T1, typename T2>
  static void gt(const T1& first, const T2& second,
                 const std::string& message = std::string{}) {
    if (first <= second) {
      std::stringstream exmsg_stream;
      exmsg_stream << "<test::gt failed!> " << message << " [first: " << first
                   << "] [second: " << second << "]";
      throw test_exception(exmsg_stream.str());
    }
  }

  template <typename T1, typename T2>
  static void lt(const T1& first, const T2& second,
                 const std::string& message = std::string{}) {
    if (first >= second) {
      std::stringstream exmsg_stream;
      exmsg_stream << "<test::lt failed!> " << message << " [first: " << first
                   << "] [second: " << second << "]";
      throw test_exception(exmsg_stream.str());
    }
  }

  template <typename T1, typename T2>
  static void geq(const T1& first, const T2& second,
                  const std::string& message = std::string{}) {
    if (first < second) {
      std::stringstream exmsg_stream;
      exmsg_stream << "<test::geq failed!> " << message << " [first: " << first
                   << "] [second: " << second << "]";
      throw test_exception(exmsg_stream.str());
    }
  }

  template <typename T1, typename T2>
  static void leq(const T1& first, const T2& second,
                  const std::string& message = std::string{}) {
    if (first > second) {
      std::stringstream exmsg_stream;
      exmsg_stream << "<test::leq failed!> " << message << " [first: " << first
                   << "] [second: " << second << "]";
      throw test_exception(exmsg_stream.str());
    }
  }

  template <typename T1, typename T2>
  static void container_equal(const T1& first, const T2& second,
                              const std::string& message = std::string{}) {
    if (first.size() != second.size()) {
      std::stringstream exmsg_stream;
      exmsg_stream << "<test::container_equal failed: "
                   << (first.size() > second.size() ? "first" : "second")
                   << " container is bigger> " << message;
      throw test_exception(exmsg_stream.str());
    }
    auto first_it = first.cbegin();
    auto second_it = second.cbegin();
    std::size_t i = 0;
    // Since containers have same lengths...
    while (first_it != first.cend()) {
      if (*first_it != *second_it) {
        std::stringstream exmsg_stream;
        exmsg_stream << "<test::container_equal failed: " << *first_it
                     << " != " << *second_it << " at index #" << i << "> "
                     << message;
        throw test_exception(exmsg_stream.str());
      }
      first_it++;
      second_it++;
      i++;
    }
  }

  template <typename T1, typename T2>
  static void container_not_equal(const T1& first, const T2& second,
                                  const std::string& message = std::string{}) {
    if (first.size() != second.size()) return;

    auto first_it = first.cbegin();
    auto second_it = second.cbegin();
    bool eq_flag = true;
    // Since containers have same lengths...
    while (first_it != first.cend()) {
      if (*first_it != *second_it) {
        eq_flag = false;
        break;
      }
      first_it++;
      second_it++;
    }

    if (eq_flag) {
      std::stringstream exmsg_stream;
      exmsg_stream << "<test::container_not_equal failed!> " << message;
      throw test_exception(exmsg_stream.str());
    }
  }
};
}
#endif
