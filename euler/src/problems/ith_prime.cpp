#include <cmath>
#include <cstdint>
#include <iostream>
#include <vector>

void ith_prime(int n) {

  // A simple guess
  int64_t limit = pow(n, 2);

  std::vector<bool> sieve(limit, true);

  for (int i = 2; i < sqrt(limit); i++) {
    if (sieve[i]) {
      for (int j = pow(i, 2); j <= limit; j += i) {
        sieve[j] = false;
      }
    }
  }

  int prime_count = 0;
  for (int i = 2; i < limit; i++) {
    if (sieve[i]) {
      // cout << "The " << prime_count << "th prime is " << i << endl;
      prime_count++;

      if (prime_count == n) {
        std::cout << "The " << prime_count << "th prime is " << i << "\n";
      }
    }
  }
}
