#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <numeric>
#include <vector>

#include "utils/utils.hpp"

template <typename Iterator, typename T = typename std::iterator_traits<Iterator>::value_type>
T digits_to_int(Iterator begin, Iterator end) {
  T i{0};
  for (; begin != end; ++begin) {
    i *= 10;
    i += *begin;
  }

  return i;
}

void substring_divisibility() {

  std::vector<int64_t> with_property{};
  int64_t total{0};

  std::vector<int64_t> digits{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  std::vector<int64_t> divisors{0, 2, 3, 5, 7, 11, 13, 17};

  // To test a known case as the first…
  // std::vector<int64_t> digits{1, 4, 0, 6, 3, 5, 7, 2, 8, 9};
  // std::prev_permutation(digits.begin(), digits.end());

  int64_t initial = digits_to_int(digits.begin(), digits.end());

  while (true) {

    std::next_permutation(digits.begin(), digits.end());

    // Check before the hack as initial begins with a zero.
    int64_t todo = digits_to_int(digits.begin(), digits.end());
    if (initial == todo) {
      break;
    }

    // Quick hack to ignore leading zeros
    if (digits[0] == 0) {
      continue;
    }

    bool property_satisfied = true;

    for (int64_t a{1}; a < 8; ++a) {
      int64_t part = digits_to_int(digits.begin() + a, digits.begin() + a + 3);
      if (part % divisors[a] != 0) {

        property_satisfied = false;
        break;
      }
    }

    if (property_satisfied) {
      with_property.push_back(todo);
      total += todo;
    }
  }

  for (auto x : with_property) {
    std::cout << x << "\n";
  }

  std::cout << total << "\n";
};
