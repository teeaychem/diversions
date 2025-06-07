#include <cstddef>
#include <cstdint>
#include <iostream>
#include <vector>

#include "utils/utils.hpp"

int64_t make_number(std::vector<int64_t> &digits) {
  int64_t n{0};
  for (size_t i{0}; i < digits.size(); ++i) {
    n *= 10;
    n += digits.at(i);
  }

  return n;
};

void pandigital_prime() {

  std::vector<int64_t> digits{1, 2, 3, 4, 5, 6, 7, 8, 9};

  std::vector<std::vector<int64_t>> combinations{
      {1}, {1, 2}, {1, 2, 3}, {1, 2, 3, 4}, {1, 2, 3, 4, 5}, {1, 2, 3, 4, 5, 6}, {1, 2, 3, 4, 5, 6, 7}, {1, 2, 3, 4, 5, 6, 7, 8}, {1, 2, 3, 4, 5, 6, 7, 8, 9}

  };

  int64_t max_prime{0};

  for (std::vector<int64_t> combo : combinations) {

    int64_t initial = make_number(combo);

    while (true) {
      std::next_permutation(combo.begin(), combo.end());
      int64_t todo = make_number(combo);

      if (euler::utils::is_prime_by_trial(todo)) {
        std::cout << "Prime: " << todo << "\n";
        max_prime = std::max(max_prime, todo);
      }

      if (todo == initial) {
        break;
      }
    }
  }

  std::cout << max_prime << "\n";
};
