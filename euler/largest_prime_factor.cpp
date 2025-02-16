#include <iostream>

using namespace std;

int main(int argc, char **argv) {

  int64_t n = std::stol(argv[1]);

  cout << "The largest prime factor of " << n << " is ";

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

  cout << n << endl;

  return 0;
}
