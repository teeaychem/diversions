#include "utils/niche.hpp"
#include <cstdint>
#include <iostream>
#include <set>
#include <utility>

void amicable_numbers() {

  std::set<std::pair<uint64_t, uint64_t>> amicalbe_pairs{};

  for (uint64_t i{1}; i < 10000; ++i) {

    uint64_t pds = euler::niche::proper_divisor_sum(i);
    if (pds != i && euler::niche::proper_divisor_sum(pds) == i) {
      amicalbe_pairs.insert(std::make_pair(std::min(i, pds), std::max(i, pds)));
    }
  }

  uint64_t amicable_sum{0};

  for (auto pair : amicalbe_pairs) {
    amicable_sum += pair.first + pair.second;
  }

  std::cout << amicable_sum << "\n";
}
