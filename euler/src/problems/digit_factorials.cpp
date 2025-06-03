#include "utils/utils.hpp"
#include <BigInt.hpp>
#include <cstdint>

/*
  Similar to other problems, the primary task is determining some bound after
which the sum of factorials of digits of some number will never equal that
number.

Here, this is determined by counting the digits in the largest possible
factorial sum.

After that, a search through all possible numbers is performed.

For slight performance, the relevant factorials are cached.

Though, something has been overlooked as this is rather slow.
 */
void digit_factorials() {

  typedef int64_t T;

  T digit_factorials[10];
  for (int64_t i{0}; i < 10; i++) {
    digit_factorials[i] = euler::utils::factorial_unchecked(i);
    std::cout << i << "! = " << digit_factorials[i] << "\n";
  }

  T digit_limit{1};

  for (; true; ++digit_limit) {
    T largest_factorial_sum = digit_limit * digit_factorials[9];
    std::cout << digit_limit << " : " << largest_factorial_sum << "\n";
    if (euler::utils::count_digits(largest_factorial_sum) < digit_limit) {
      digit_limit--;
      break;
    }
  }

  for (T target{3}; target < pow(10, digit_limit); ++target) {

    T factorial_sum{0};
    auto digits = euler::utils::digits_reversed(target);
    for (auto digit : digits) {
      factorial_sum += digit_factorials[digit];
    }

    if (factorial_sum == target) {
      std::cout << target << " - " << factorial_sum << "\n";
    }
  }
}
