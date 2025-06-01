#include <iostream>

void sum_square_difference(int n) {
  int64_t sum = (n * (n + 1)) / 2;
  int64_t sum_square = pow(sum, 2);

  int64_t square_sum = 0;
  for (int i = 1; i <= n; i++) {
    square_sum += pow(i, 2);
  }

  std::cout << sum_square - square_sum << "\n";
}
