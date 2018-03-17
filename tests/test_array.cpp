#include <algorithm>
#include <array>
#include <iostream>
#include <phoenix/array.hpp>
#include <phoenix/test.hpp>

void create_array() {
  phoenix::array<int, 10> a;
  std::array<int, 10> comp_a{};
  phoenix::test::eq(a.size(), 10u, "Array size is not equal 10");
  phoenix::test::container_equal(a, comp_a, "Array is not equal to raw array equivalent");

  phoenix::array<int, 10> b(3);
  std::array<int, 10> comp_b{};
  std::fill(comp_b.begin(), comp_b.end(), 3);
  phoenix::test::container_equal(b, comp_b, "Array constructed with fill value isn't filled properly");

  phoenix::array<int, 3> c{1, 2, 3};
  std::array<int, 3> comp_c{1, 2, 3};
  phoenix::test::container_equal(c, comp_c, "Array constructed with init-list has wrong content");

  phoenix::array<int, 5> d{2, 3, 4};
  std::array<int, 5> comp_d{2, 3, 4};
  phoenix::test::container_equal(d, comp_d, "Array constructed with init-list #2 has wrong content");

  try {
    phoenix::array<int, 3> e{2, 3, 4, 5, 6};
    std::cout << "Created array with larger init-list!" << std::endl;
  } catch (...) {
  }

  std::array<char, 4> f{'a', 'b', 'c', 'd'};
  phoenix::array<char, 4> comp_f(f);

  phoenix::test::container_equal(f, comp_f, "Array constructed from std::array isn't the same!");
}

void copy_ctors() {
  phoenix::array<int, 3> a{1, 2, 3};
  phoenix::array<int, 3> b(a);

  phoenix::test::container_equal(a, b, "Copy-constructed container isn't equal to original one!");

  phoenix::array<int, 5> c{2, 4, 6, 8, 10};
  phoenix::array<int, 5> d = c;

  phoenix::test::container_equal(c, d, "Copied container isn't equal to original one!");
}

void access() {
  phoenix::array<char, 10> arr{'a', 'b', 'c', 'd', 'e',
                               'f', 'g', 'h', 'i', 'j'};

  // raw access
  phoenix::test::eq(arr[3], 'd');
  arr[5] = 'h';
  phoenix::test::eq(arr[5], 'h');

  // guarded access
  phoenix::test::eq(arr.at(2), 'c');
  arr.at(4) = 'y';
  phoenix::test::eq(arr.at(4), 'y');

  try {
    arr.at(10);
    arr.at(15);
    std::cout << "Array accessed outside of bounds!" << std::endl;
  } catch (...) {
  }

  try {
    arr.at(-3);
    std::cout << "Array accessed outside of negative bounds!" << std::endl;
  } catch (...) {
  }
}

int main() {
  phoenix::run_test(create_array, "Create array");
  phoenix::run_test(copy_ctors, "Copy constructors");
  phoenix::run_test(access, "Access");
}
