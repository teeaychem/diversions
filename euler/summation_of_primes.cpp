#include <iostream>
#include <string>
#include <sys/_types/_u_int64_t.h>
#include <vector>

using namespace std;

int main(int argc, char **argv) {

  u_int64_t n = stoi(argv[1]);

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
