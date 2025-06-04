#include "utils/utils.hpp"
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

void double_base_palindromes() {

  int64_t sum{0};

  for (int64_t i{1}; i <= pow(10, 6); ++i) {
    if (euler::utils::is_palindromic(std::to_string(i))) {
      auto bv = euler::utils::as_base_two_bit_vec(i);
      if (euler::utils::is_palindromic(bv)) {
        sum += i;
      }
    }
  }

  std::cout << sum << "\n";
}
