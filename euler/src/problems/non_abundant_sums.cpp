#include "utils/utils.hpp"
#include <cstdint>
#include <iostream>
#include <vector>

void non_abundant_sums() {

  std::vector<int16_t> abundant_numbers{};
  std::vector<int64_t> sums_of_two_abundant{};
  int64_t non_abundant_sum{0};

  for (int64_t n{12}; n <= 28123; ++n) {
    if (euler::utils::proper_divisor_sum(n) > n) {
      abundant_numbers.push_back(n);
    }
  }
  std::cout << "\n";

  for (auto i{0}; i < abundant_numbers.size(); ++i) {
    int64_t ith = abundant_numbers.at(i);
    for (auto j{0}; j < abundant_numbers.size(); ++j) {
      int64_t jth = abundant_numbers.at(j);
      if (ith + jth <= 28123) {
        sums_of_two_abundant.push_back(ith + jth);
      }
    }
  }

  sort(sums_of_two_abundant.begin(), sums_of_two_abundant.end());
  sums_of_two_abundant.erase(
      unique(sums_of_two_abundant.begin(), sums_of_two_abundant.end()),
      sums_of_two_abundant.end());

  size_t idx{0};
  int64_t by_one{0};

  while (idx < sums_of_two_abundant.size()) {
    if (sums_of_two_abundant.at(idx) == by_one) {
      idx++;
    } else {
      non_abundant_sum += by_one;
    }
    by_one++;
  }

  std::cout << non_abundant_sum << "\n";
};
