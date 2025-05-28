#include <cmath>
#include <iostream>
using namespace std;

int64_t factors(int64_t n) {
  int64_t count = 0;
  for (int64_t i = 1; i <= sqrt(n); i++) {
    if (n % i == 0) {

      count++;
      if (n / i != i) {

        count++;
      }
    }
  }

  return count;
}

void highly_divisible_triangular_number() {

  int64_t i = 1;
  int64_t triangle = 1;
  int64_t f = 0;

  while (true) {
    f = factors(triangle);

    if (f < 500) {
      i += 1;
      triangle += i;

    } else {
      break;
    }
  }

  cout << triangle << " " << f << endl;
}
