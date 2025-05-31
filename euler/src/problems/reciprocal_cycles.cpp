#include "utils/utils.hpp"
#include <cstdint>
#include <iostream>
#include <set>
#include <vector>

std::vector<uint64_t> decimal_representation(uint64_t numerator,
                                             uint64_t denominator) {
  std::vector<uint64_t> fraction{};
  std::set<uint64_t> dividends{numerator};

  uint64_t tmp;
  bool fresh_dividends = true;

  while (fresh_dividends) {
    tmp = numerator / denominator;
    fraction.push_back(tmp);
    numerator = 10 * (numerator - (tmp * denominator));

    fresh_dividends = dividends.insert(numerator).second;
  }
  return fraction;
}

void reciprocal_cycles() {

  std::vector<uint64_t> representation;

  uint64_t maximum_denominator{0};
  size_t maximum_cycle{0};

  for (uint64_t denominator{1}; denominator <= 1000; denominator++) {
    representation = decimal_representation(1, denominator);

    if (*representation.rbegin() != 0) {
      if (maximum_cycle < (representation.size() - 1)) {
        maximum_cycle = representation.size() - 1;
        maximum_denominator = denominator;
      }
    }
  }

  std::cout << maximum_denominator << "\n";
};
