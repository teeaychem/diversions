#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char **argv) {

  int n = stoi(argv[1]);

  // A simple guess
  int64_t limit = pow(n, 2);

  vector<bool> sieve(limit, true);

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
        cout << "The " << prime_count << "th prime is " << i << endl;
      }
    }
  }

  return 0;
}
