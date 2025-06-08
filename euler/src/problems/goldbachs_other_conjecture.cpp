#include "utils/utils.hpp"
#include <algorithm>
#include <cstdint>
#include <iostream>

void goldbachs_other_conjecture() {

  int64_t limit = pow(2, 16);

  std::vector<int64_t> primes = euler::utils::primes_below(limit);
  std::vector<int64_t> squares{};

  for (int64_t i{1};; ++i) {
    int64_t squared = pow(i, 2);
    if (limit <= squared) {
      break;
    } else {
      squares.push_back(2 * squared);
    }
  }

  for (int64_t i{3}; i < limit; i += 2) {

    bool counterexample = true;

    for (size_t p{0}; p < primes.size(); ++p) {
      int64_t prime = primes.at(p);

      if (std::binary_search(primes.begin(), primes.end(), i)) {
        counterexample = false;
        break;
      }

      if (std::binary_search(squares.begin(), squares.end(), i - prime)) {
        counterexample = false;
        break;
      }

      if (i < prime) {
        break;
      }
    }

    if (counterexample) {
      std::cout << i << "\n";
      return;
    }
  }
}
