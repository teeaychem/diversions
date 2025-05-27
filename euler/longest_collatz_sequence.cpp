#include <iostream>
using namespace std;

int collatz_length(unsigned long long n) {
  int steps{0};

  while (n != 1) {
    steps++;
    if ((n & 1) == 0) {
      n = (n / 2);
    } else {
      n = (3 * n + 1);
    }
  }

  return steps;
}

int main() {

  int max_n{1};
  int max_length{1};

  for (int i = 2; i < 1000000; ++i) {
    int length = collatz_length(i);
    if (max_length < length) {
      max_n = i;
      max_length = length;
    }
  }

  cout << max_n << " : " << max_length << "\n";
}
