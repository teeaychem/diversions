#include "utils/utils.hpp"
#include <cstdint>
#include <iostream>
#include <vector>
void champernownes_constant() {

  std::vector<int64_t> digits{};
  digits.push_back(0);

  for (int64_t i{1}; digits.size() <= 1000000; ++i) {
    int64_t n = i;

    auto eyes = euler::utils::digits_reversed(i);
    for (auto it = eyes.rbegin(); it != eyes.rend(); ++it) {
      digits.push_back(*it);
    }
  }

  int64_t product{1};
  for (size_t i{0}; i < 7; ++i) {
    int64_t digit = digits.at(pow(10, i));

    std::cout << digit << " " << pow(10, i) << "\n";
    product *= digit;
  }

  std::cout << product << std::endl;
}
