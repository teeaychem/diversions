#include <cstdint>
#include <iostream>
#include <set>
#include <utility>

uint64_t proper_divisor_sum(uint64_t n) {
  uint64_t divisor_sum{0};
  for (uint64_t divisor{0}; divisor < n; ++divisor) {
    if (n % divisor == 0) {
      divisor_sum += divisor;
    }
  }

  return divisor_sum;
}

void amicable_numbers() {

  std::set<std::pair<uint64_t, uint64_t>> amicalbe_pairs{};

  for (uint64_t i{1}; i < 10000; ++i) {

    uint64_t pds = proper_divisor_sum(i);
    if (pds != i && proper_divisor_sum(pds) == i) {
      amicalbe_pairs.insert(std::make_pair(std::min(i, pds), std::max(i, pds)));
    }
  }

  uint64_t amicable_sum{0};

  for (auto pair : amicalbe_pairs) {
    amicable_sum += pair.first + pair.second;
  }

  std::cout << amicable_sum << "\n";
}
