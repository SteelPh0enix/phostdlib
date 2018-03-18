#include <iostream>
#include <phoenix/test.hpp>
#include <phoenix/vector.hpp>
#include <utility>
#include <vector>

void create_vector() {
  // Simple c-tor
  phoenix::vector<int> vec1;
  phoenix::test::eq(vec1.size(), 0u, "Vector constructed by default isn't empty");

  // c-tor with size
  phoenix::vector<int> vec2(10);
  phoenix::test::eq(vec2.size(), 10u, "Vector constructed with size = 10 doesn't have size = 10");

  // init-list c-tor
  std::initializer_list<int> data{1, 2, 3};
  phoenix::vector<int> vec3(data);
  phoenix::test::eq(vec3.size(), data.size(), "Vector constructed with init list has different size");
  phoenix::test::container_equal(vec3, std::vector<int>(data),
                                   "Vector constructed with init-list isn't "
                                   "equal to std::vector constructed with the same init-list");

}

void rule_of_five() {
  // copy c-tor
  phoenix::vector<int> vecc1{1, 2, 3, 4};
  phoenix::vector<int> vecc2(vecc1);

  phoenix::test::container_equal(vecc1, vecc2, "Vector constructed with copy c-tor isn't same as original");
  phoenix::test::neq(vecc1.begin(), vecc2.begin(), "(copy c-tor) Vectors point to the same data");

  // move c-tor
  std::vector<int> vecm1_data{2, 4, 6, 8, 10};
  phoenix::vector<int> vecm1(vecm1_data);
  phoenix::vector<int> vecm2(std::move(vecm1));

  phoenix::test::eq(vecm1.size(), 0u, "(move c-tor) Original vector size is not 0");
  phoenix::test::eq(vecm1.capacity(), 0u);
  phoenix::test::container_equal(vecm2, vecm1_data,
                                 "(move c-tor) Moved vector data is not equal the original data");

  // copy operator
  phoenix::vector<int> vecc3{1, 2, 3, 4, 5, 6, 7, 8};
  phoenix::vector<int> vecc4 = vecc3;

  phoenix::test::container_equal(vecc3, vecc4,
                                 "(copy operator) Copied vector data isn't equal to original vector data");
  phoenix::test::neq(vecc3.begin(), vecc4.begin(), "(copy operator) Vectors point to the same data");

  // move operator
  std::vector<int> vecm_org{6, 3, 2, 45, 664};
  phoenix::vector<int> vecm3(vecm_org);
  phoenix::vector<int> vecm4 = std::move(vecm3);

  phoenix::test::eq(vecm3.size(), 0u, "(move operator) Original vector size is not equal 0");
  phoenix::test::eq(vecm3.capacity(), 0u, "(move operator) Original vector capacity is not equal 0");
  phoenix::test::container_equal(vecm4, vecm_org, "(move operator) Moved data is not equal original now");
}

void push_pop() {
  phoenix::vector<int, 4> v;

  v.push(10);
  v.push(20);
  v.push(30);

  phoenix::test::eq(v.size(), 3u, "Vector size is not equal 3 after pushing 3 elements");
  phoenix::test::eq(v.capacity(), 4u, "Vector capacity is not equal 4 after pushing "
                                      "3 elements (AllocSize = 4)");

  v.push(20);
  phoenix::test::eq(v.size(), 4u, "Vector size is not equal 4 after pussing 4 elements");
  phoenix::test::eq(v.capacity(), 4u, "Vector capacity is not equal 4 after pushing "
                                      "4 elements (AllocSize = 4)");

  v.push(10);
  phoenix::test::eq(v.size(), 5u, "Vector size is not equal 5 after pussing 5 elements");
  phoenix::test::eq(v.capacity(), 8u, "Vector capacity is not equal 8 after pushing "
                                      "5 elements (AllocSize = 4)");

  phoenix::test::eq(v.pop(), 10, "Last element is not equal 30!");
  phoenix::test::eq(v.size(), 4u, "size isn't 2 after poping");
  phoenix::test::eq(v.capacity(), 8u, "Capacity has changed after popping");

  v.resize(0);
  try {
    v.pop();
    std::cout << "Popped out beyond range!\n";
  } catch (...) {
  }
}

void access() {
  phoenix::vector<char> v{'a', 'b', 'c', 'd', 'e'};

  // unguarded access
  phoenix::test::eq(v[0], 'a');
  v[3] = 'q';
  phoenix::test::eq(v[3], 'q');

  // guarded acces
  phoenix::test::eq(v.at(1), 'b');
  v.at(4) = 'o';
  phoenix::test::eq(v.at(4), 'o');
  try {
    v.at(-3);
    std::cout << "Guarded access out of negative bounds!" << std::endl;
  } catch (...) {
  }

  try {
    v.at(10);
    std::cout << "Guarded access out of bounds!" << std::endl;
  } catch (...) {
  }
}

void iterator() {
  phoenix::vector<int> a{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  // construction
  phoenix::test::eq(a.cbegin(), phoenix::vector<int>::const_iterator(&a[0]));
  phoenix::test::eq(a.begin(), phoenix::vector<int>::iterator(&a[0]));
  phoenix::test::eq(a.cend(), phoenix::vector<int>::const_iterator(&a[0] + 10));
  phoenix::test::eq(a.end(),phoenix::vector<int>::iterator(&a[0] + 10));

  // dereferencing
  phoenix::test::eq(*a.begin(), a[0]);
  phoenix::test::eq(*a.cbegin(), a[0]);
  phoenix::test::eq(a.begin().operator->(), &a[0]);
  phoenix::test::eq(a.cbegin().operator->(), &a[0]);

  // incrementation and decrementation
  {
    auto it = a.begin() + 3;
    phoenix::test::eq(*++it, a[4]);
    phoenix::test::eq(*--it, a[3]);
    phoenix::test::eq(*it++, a[3]);
    phoenix::test::eq(*it, a[4]);
    phoenix::test::eq(*it--, a[4]);
    phoenix::test::eq(*it, a[3]);
  }

  {
    auto it = a.cbegin() + 5;
    phoenix::test::eq(*++it, a[6]);
    phoenix::test::eq(*--it, a[5]);
    phoenix::test::eq(*it++, a[5]);
    phoenix::test::eq(*it, a[6]);
    phoenix::test::eq(*it--, a[6]);
    phoenix::test::eq(*it, a[5]);
  }

  // value comparsion and add/sub
  phoenix::test::eq(*a.begin(), a[0]);
  phoenix::test::eq(*(a.begin() + 3), a[3]);
  phoenix::test::eq(*(a.end() - 1), a[9]);

  phoenix::test::eq(*a.cbegin(), a[0]);
  phoenix::test::eq(*(a.cbegin() + 3), a[3]);
  phoenix::test::eq(*(a.cend() - 1), a[9]);

  {
    auto it = a.begin();
    it += 3;
    phoenix::test::eq(*it, a[3]);
    it -= 2;
    phoenix::test::eq(*it, a[1]);
  }

  {
    auto it = a.cend();
    it -= 4;
    phoenix::test::eq(*it, a[6]);
    it += 2;
    phoenix::test::eq(*it, a[8]);
  }

  // comparsion
  phoenix::test::neq(a.begin(), a.end());
  phoenix::test::eq(a.begin() + 2, a.end() - 8);
  phoenix::test::neq(a.cbegin(), a.cend());
  phoenix::test::eq(a.cbegin() + 3, a.cend() - 7);

  // manual iteration
  for(auto it = a.begin(); it != a.end(); it++) {
    *(it)++;
  }

  {
    std::size_t i = 0;
    for (auto it = a.cbegin(); it != a.cend(); it++) {
      phoenix::test::eq(*it, a[i]);
      i++;
    }
  }

  // range-based for iteration
  for(auto& e: a) {
    e++;
  }

  {
    std::size_t i = 0;
    for (const auto &e: a) {
      phoenix::test::eq(e, a[i]);
      i++;
    }
  }

  // Adress dereferencing test
  {
    std::size_t i = 0;
    for(const auto& e: a) {
      phoenix::test::eq(&e, &a[i], "Dereferenced iterator didn't returned the address of element!");
      i++;
    }
  }
}

int main() {
  phoenix::run_test(create_vector, "Create vector");
  phoenix::run_test(iterator, "Iterator");
  phoenix::run_test(rule_of_five, "Rule of five");
  phoenix::run_test(push_pop, "Push/pop");
  phoenix::run_test(access, "Access");
}
