#include "utils/display.hpp"
#include "utils/utils.hpp"
#include <cstdint>

/*
  p = n^2 + an + b
    = n(n + a) + b

  As starting with n = 0, b must be a prime.
  This also implies 0 < b.
  As consecutive values of n, 1 + a + b must a prime.
  That is, a = p - (1 + b) for some prime p.

 */
void quadratic_primes() {

  auto primes = euler::utils::primes_below(4000);

  int64_t max_consecutive{0};
  int64_t max_a{0};
  int64_t max_b{0};

  auto check_coefficients = [&max_consecutive, &max_a, &max_b](int64_t a,
                                                               int64_t b) {
    if (abs(a) < 1000 && abs(b) <= 1000) {

      int64_t n{2};
      while (euler::utils::is_prime_by_trial((n * n) + (a * n) + b)) {
        ++n;
      }

      if (max_consecutive < n) {

        max_a = a;
        max_b = b;
        max_consecutive = n;
      }
    }
  };

  for (auto b_it = primes.begin(); b_it != primes.end(); ++b_it) {

    for (auto a_it = primes.rbegin(); a_it != primes.rend(); ++a_it) {

      check_coefficients(*a_it - (*b_it + 1), *b_it);
    }
  }

  std::cout << "max_consecutive: " << max_consecutive << "\n";
  std::cout << "\ta: " << max_a << "\n";
  std::cout << "\tb: " << max_b << "\n";
  std::cout << "\ta * b: " << max_a * max_b << "\n";
};
