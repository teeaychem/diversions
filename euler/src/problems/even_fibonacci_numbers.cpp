#include <iostream>

void even_fibonacci_numbers(int limit) {
  int a{1};
  int b{2};

  int swap{0};

  int even_sum{2};

  while (true) {
    swap = b;
    b = a + b;
    a = swap;

    if (b >= limit) {
      break;
    }

    if (b % 2 == 0) {
      even_sum += b;
    }

    std::cout << b << " ";
  }

  std::cout << "\n";

  std::cout << even_sum << "\n";
}
