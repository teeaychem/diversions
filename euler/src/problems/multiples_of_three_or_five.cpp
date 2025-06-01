#include <iostream>
void multiples_of_three_or_five(int limit) {
  int sum = 0;

  for (int i = 1; i < limit; i++) {
    if (i % 3 == 0 || i % 5 == 0) {
      sum += i;
    }
  }
  std::cout << sum << "\n";
};
