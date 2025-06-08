#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <vector>

#include "utils/utils.hpp"

void consecutive_prime_sum() {

  int64_t limit{1000000};

  size_t seq{1};

  size_t max_seq{1};
  int64_t max_sum{};
  int64_t start{0};
  int64_t end{0};

  std::vector<int64_t> primes = euler::utils::primes_below(limit);

  for (size_t i{0}; i < primes.size() - 1; ++i) {
    int64_t sum = primes.at(i);
    size_t count = 1;

    for (size_t j{i + 1}; j < primes.size(); ++j) {
      sum += primes.at(j);

      if (limit < sum) {
        break;
      }

      count++;
      if (std::binary_search(primes.begin(), primes.end(), sum)) {
        if (max_seq < count) {
          max_seq = count;
          max_sum = sum;
          start = i;
          end = j;
        }
      }
    }
  }

  std::cout << max_seq << " " << start << " " << end << " " << max_sum << "\n";
}
