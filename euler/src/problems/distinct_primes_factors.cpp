#include "utils/utils.hpp"
#include <cstdint>
#include <iostream>

void distinct_primes_factors() {

  size_t count{0};
  int64_t n{1};
  int64_t target{4};

  while (true) {
    if (n == INT64_MAX) {
      std::cout << "Ek" << "\n";
      std::exit(-1);
    }

    auto fs = euler::utils::unique_prime_factors(n);

    if (euler::utils::unique_prime_factors(n).size() == target) {
      count++;

      if (count == target) {
        std::cout << "Last: " << n << "\n";
        break;
      }
    } else {
      count = 0;
    }

    ++n;
  }

  for (int64_t i = n - (target - 1); i <= n; i++) {
    std::cout << i << "\t";
    auto fs = euler::utils::unique_prime_factors(i);
    for (auto f : fs) {
      std::cout << f << " ";
    }
    std::cout << "\n";
  }
}
