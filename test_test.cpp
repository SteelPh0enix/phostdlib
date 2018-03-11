#include <phoenix/test.hpp>
#include <iostream>
#include <vector>

void eq() {
  try {
    phoenix::test::eq(2, 2, "2 is not equal 2");
  } catch (const std::exception& e) {
    std::cout << e.what() << std::endl;
  }

  try {
    phoenix::test::eq(2, 3, "2 is not equal 3");
  } catch (const std::exception& e) {
    std::cout << e.what() << std::endl;
  }
}

void neq() {
  try {
    phoenix::test::neq(2, 2, "2 is equal 2");
  } catch (const std::exception& e) {
    std::cout << e.what() << std::endl;
  }

  try {
    phoenix::test::neq(2, 3, "2 is equal 3");
  } catch (const std::exception& e) {
    std::cout << e.what() << std::endl;
  }
}

void gt() {
  try {
    phoenix::test::gt(2, 2, "2 is not greater than 2");
  } catch (const std::exception& e) {
    std::cout << e.what() << std::endl;
  }

  try {
    phoenix::test::gt(2, 3, "2 is not greater than 3");
  } catch (const std::exception& e) {
    std::cout << e.what() << std::endl;
  }
  try {
    phoenix::test::gt(5, 3, "5 is not greater than 3");
  } catch (const std::exception& e) {
    std::cout << e.what() << std::endl;
  }
}

void lt() {
  try {
    phoenix::test::lt(2, 2, "2 is not less than 2");
  } catch (const std::exception& e) {
    std::cout << e.what() << std::endl;
  }

  try {
    phoenix::test::lt(2, 3, "2 is not less than 3");
  } catch (const std::exception& e) {
    std::cout << e.what() << std::endl;
  }
  try {
    phoenix::test::lt(5, 3, "5 is not less than 3");
  } catch (const std::exception& e) {
    std::cout << e.what() << std::endl;
  }
}

void geq() {
  try {
    phoenix::test::geq(2, 2, "2 is not greater or equal 2");
  } catch (const std::exception& e) {
    std::cout << e.what() << std::endl;
  }

  try {
    phoenix::test::geq(2, 3, "2 is not greater or equal 3");
  } catch (const std::exception& e) {
    std::cout << e.what() << std::endl;
  }
  try {
    phoenix::test::geq(5, 3, "5 is not greater or equal 3");
  } catch (const std::exception& e) {
    std::cout << e.what() << std::endl;
  }
}

void leq() {
  try {
    phoenix::test::leq(2, 2, "2 is not less or equal 2");
  } catch (const std::exception& e) {
    std::cout << e.what() << std::endl;
  }

  try {
    phoenix::test::leq(2, 3, "2 is not less or equal 3");
  } catch (const std::exception& e) {
    std::cout << e.what() << std::endl;
  }
  try {
    phoenix::test::leq(5, 3, "5 is not less or equal 3");
  } catch (const std::exception& e) {
    std::cout << e.what() << std::endl;
  }
}

void containers_equal() {
  try {
    std::vector<int> a{1, 2, 3, 4, 5};
    std::vector<int> b{1, 2, 3, 4, 5};
    phoenix::test::container_equal(a, b, "containers are not equal");
  } catch (const std::exception& e) {
    std::cout << e.what() << std::endl;
  }

  try {
    std::vector<int> a{1, 2, 3, 4, 5};
    std::vector<int> b{1, 2, 3, 45, 5};
    phoenix::test::container_equal(a, b, "containers are not equal");
  } catch (const std::exception& e) {
    std::cout << e.what() << std::endl;
  }

  try {
    std::vector<int> a{1, 2, 3, 4, 5};
    std::vector<int> b{1, 2, 3, 4};
    phoenix::test::container_equal(a, b, "containers are not equal");
  } catch (const std::exception& e) {
    std::cout << e.what() << std::endl;
  }
}

void containers_not_equal() {
  try {
    std::vector<int> a{1, 2, 3, 4, 5};
    std::vector<int> b{1, 2, 3, 4, 5};
    phoenix::test::container_not_equal(a, b, "containers are equal");
  } catch (const std::exception& e) {
    std::cout << e.what() << std::endl;
  }

  try {
    std::vector<int> a{1, 2, 3, 4, 5};
    std::vector<int> b{1, 2, 3, 45, 5};
    phoenix::test::container_not_equal(a, b, "containers are equal");
  } catch (const std::exception& e) {
    std::cout << e.what() << std::endl;
  }

  try {
    std::vector<int> a{1, 2, 3, 4, 5};
    std::vector<int> b{1, 2, 3, 4};
    phoenix::test::container_not_equal(a, b, "containers are equal");
  } catch (const std::exception& e) {
    std::cout << e.what() << std::endl;
  }
}

int main() {
  eq();
  neq();
  gt();
  lt();
  geq();
  leq();
  containers_equal();
  containers_not_equal();
}
