#include <cmath>
#include <cstdint>
#include <iostream>
#include <utils/utils.hpp>
#include <vector>

using namespace euler;

void digit_fifth_powers() {

  /*
    Limit the search by determining a limit on the number of digts.
    As, d * 9^5 is the max representable using d, so when digits(d * 9^5) < d,
    it won't be possible to create a number of appropriate length.

   */
  int64_t nine_to_five = pow(9, 5);
  int64_t digits{1};

  while (utils::digits_reversed(digits * nine_to_five).size() > digits) {
    digits++;
  }
  std::cout << digits << "\n";

  auto raise_five = [](std::vector<int64_t> &digits) -> int64_t {
    int64_t sum{0};
    for (auto digit : digits) {
      sum += pow(digit, 5);
    }

    return sum;
  };

  /*
    With a limit found, check everything…
   */

  std::vector<int64_t> surprises{};

  for (int64_t n{2}; n < digits * nine_to_five; ++n) {
    std::vector<int64_t> digits = utils::digits_reversed(n);
    if (n == raise_five(digits)) {
      surprises.push_back(n);
    }
  }

  int64_t surprise_sum{0};

  for (auto surprise : surprises) {
    std::cout << surprise << "\n";
    surprise_sum += surprise;
  }

  std::cout << "Sum: " << surprise_sum << "\n";
};
