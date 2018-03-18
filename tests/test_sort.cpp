#include <phoenix/test.hpp>
#include <phoenix/vector.hpp>
#include <phoenix/sort.hpp>
#include <phoenix/utility.hpp>

void insertion() {
  phoenix::vector<int> a{2, 8, 4, 1, 3, 6, 2, 3, 2, 5, 23, 67, 32, 643, 756, 4236, 34, 1, 3, 7};

  phoenix::insertion_sort(a.begin(), a.end());
  phoenix::test::eq(phoenix::is_sorted(a.begin(), a.end()), true);

  phoenix::insertion_sort(a.begin(), a.end(), phoenix::is_lesser);
  phoenix::test::eq(phoenix::is_sorted(a.begin(), a.end(), phoenix::is_lesser), true);
}

void bubble() {
  phoenix::vector<int> a{2, 8, 4, 1, 3, 6, 2, 3, 2, 5, 23, 67, 32, 643, 756, 4236, 34, 1, 3, 7};

  phoenix::bubble_sort(a.begin(), a.end());
  phoenix::test::eq(phoenix::is_sorted(a.begin(), a.end()), true);

  phoenix::insertion_sort(a.begin(), a.end(), phoenix::is_lesser);
  phoenix::test::eq(phoenix::is_sorted(a.begin(), a.end(), phoenix::is_lesser), true);
}

void selection() {
  phoenix::vector<int> a{2, 8, 4, 1, 3, 6, 2, 3, 2, 5, 23, 67, 32, 643, 756, 4236, 34, 1, 3, 7};

  phoenix::selection_sort(a.begin(), a.end());
  phoenix::test::eq(phoenix::is_sorted(a.begin(), a.end()), true);

  phoenix::selection_sort(a.begin(), a.end(), phoenix::is_lesser);
  phoenix::test::eq(phoenix::is_sorted(a.begin(), a.end(), phoenix::is_lesser), true);
}

void bogo() {
  phoenix::vector<int> a{2, 8, 4, 1, 3};

  phoenix::bogo_sort(a.begin(), a.size());
  phoenix::test::eq(phoenix::is_sorted(a.begin(), a.end()), true);

  phoenix::bogo_sort(a.begin(), a.size(), phoenix::is_lesser);
  phoenix::test::eq(phoenix::is_sorted(a.begin(), a.end(), phoenix::is_lesser), true);
}

int main() {
  phoenix::run_test(insertion, "Insertion sort");
  phoenix::run_test(bubble, "Bubble sort");
  phoenix::run_test(selection, "Selection sort");
  phoenix::run_test(bogo, "Bogo sort");
}