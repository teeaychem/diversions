#include <iostream>

void smallest_multiple(int n) {

  int smallest = 1;

  bool evenly_divisible = true;

  while (true) {

    evenly_divisible = true;

    for (int i = 1; i <= n; i++) {
      if (smallest % i != 0) {
        evenly_divisible = false;
        break;
      }
    }

    if (evenly_divisible) {
      std::cout << smallest << "\n";
      break;
    }

    smallest++;
  }
}
