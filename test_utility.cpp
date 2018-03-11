#include <iostream>
#include <phoenix/utility.hpp>
#include <phoenix/test.hpp>
#include <phoenix/array.hpp>

void test_greater() {
  try {
    phoenix::test::eq(phoenix::greater(2, 3), 3, "Is 2 greater than 3?");
    phoenix::test::eq(phoenix::greater(4, 2), 4, "Is 2 greater than 4?");
    phoenix::test::eq(phoenix::greater(3, 3), 3, "This is awkward");
  } catch (const phoenix::test_exception& e) {
    std::cout << e.what() << std::endl;
  } catch (const std::exception& e) {
    std::cout << "Non-test exception occurred: " << e.what() << std::endl;
  }
}

void test_lesser() {
  try {
    phoenix::test::eq(phoenix::lesser(2, 3), 2, "is 3 lesser than 2?");
    phoenix::test::eq(phoenix::lesser(4, 2), 2, "is 4 lesser than 2?");
    phoenix::test::eq(phoenix::lesser(3, 3), 3, "this is awkward");
  } catch (const phoenix::test_exception& e) {
    std::cout << e.what() << std::endl;
  } catch (const std::exception& e) {
    std::cout << "Non-test exception occurred: " << e.what() << std::endl;
  }
}

void test_swap() {
  try {
    int x = 3, y = 5;
    phoenix::swap(x, y);
    phoenix::test::eq(x, 5, "Values has not been swapped!");
    phoenix::test::eq(y, 3, "Values has not been swapped!");
  } catch (const phoenix::test_exception& e) {
    std::cout << e.what() << std::endl;
  } catch (const std::exception& e) {
    std::cout << "Non-test exception occurred: " << e.what() << std::endl;
  }
}

void test_is_sorted() {
  try {
    phoenix::array<int, 10> sorted{2, 4, 6, 8, 10, 23, 45, 89, 2354, 9999};
    phoenix::array<double, 10> not_sorted{3., 6., 3.14, 7.5, 2.3, 9.9, 12.3, 9., 1234., 532.};

    phoenix::test::eq(phoenix::is_sorted(sorted.begin(), sorted.end(), phoenix::is_greater), true,
                      "Sorted container is not sorted?");
    phoenix::test::eq(phoenix::is_sorted(sorted.begin(), sorted.end(), phoenix::is_lesser), false,
                      "Sorted container is sorted reverse way?");
    phoenix::test::eq(phoenix::is_sorted(not_sorted.begin(), not_sorted.end(), phoenix::is_greater), false,
                      "Unsorted container is sorted ascending!");
    phoenix::test::eq(phoenix::is_sorted(not_sorted.begin(), not_sorted.end(), phoenix::is_lesser), false,
                      "Unsorted container is sorted descending!");

  } catch (const phoenix::test_exception& e) {
    std::cout << e.what() << std::endl;
  } catch (const std::exception& e) {
    std::cout << "Non-test exception occurred: " << e.what() << std::endl;
  }
}

int main() {
  test_greater();
  test_lesser();
  test_swap();
  test_is_sorted();
}