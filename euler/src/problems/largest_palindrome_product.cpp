#include <cmath>
#include <iostream>

void largest_palindrome_product(int limit) {

  int upper = pow(10, limit);
  int lower = pow(10, limit - 1);

  int largest_product = 0;

  for (int i = upper - 1; lower <= i; i--) {
    for (int j = upper - 1; lower <= j; j--) {
      int product = i * j;

      if (largest_product < product) {

        int product_length = log10(product);
        bool palindromic = true;

        for (int x = 0; x <= product_length / 2; x++) {

          int a = (product / (int)pow(10, (product_length - x))) % 10;
          int b = (product / (int)pow(10, x)) % 10;

          if (a != b) {
            palindromic = false;
            break;
          }
        }

        if (palindromic) {
          largest_product = product;
          std::cout << i << " " << j << "\n";
        }
      }
    }
  }

  std::cout << largest_product << "\n";
}
