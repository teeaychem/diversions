#include <iostream>
void largest_prime_factor(int limit) {
  int64_t n = limit;

  std::cout << "The largest prime factor of " << n << " is ";

  if ((n % 2) == 0) {
    n /= 2;
  }

  int divisor = 3;

  while (pow(divisor, 2) <= n) {
    if ((n % divisor) == 0) {
      n /= divisor;
    } else {
      divisor += 2;
    }
  }

  std::cout << n << std::endl;
}
