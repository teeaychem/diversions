#include <iostream>
#include <sys/_types/_u_int64_t.h>
#include <vector>

using namespace std;

int summation_of_primes(int n) {

  vector<bool> sieve(n, true);

  for (int i = 2; i < sqrt(n); i++) {
    if (sieve[i]) {
      for (int j = pow(i, 2); j < n; j += i) {
        sieve[j] = false;
      }
    }
  }

  u_int64_t sum = 0;
  for (int i = 2; i < n; i++) {
    if (sieve[i]) {
      sum += i;
    }
  }

  cout << sum << endl;

  return 0;
}
