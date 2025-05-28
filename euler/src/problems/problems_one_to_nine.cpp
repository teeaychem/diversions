#include "problems.hpp"
#include <iostream>
#include <vector>

void multiples_of_three_or_five(int limit) {
  int sum = 0;

  for (int i = 1; i < limit; i++) {
    if (i % 3 == 0 || i % 5 == 0) {
      sum += i;
    }
  }
  std::cout << sum << "\n";
};

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

void largest_prime_factor(int limit) {
  int64_t n = limit;

  std::cout << "The largest prime factor of " << n << " is ";

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

  std::cout << n << std::endl;
}

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
          std::cout << i << " " << j << std::endl;
        }
      }
    }
  }

  std::cout << largest_product << "\n";
}

void smallest_multiple(int n) {

  int smallest = 1;

  bool evenly_divisible = false;

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

void sum_square_difference(int n) {
  int64_t sum = (n * (n + 1)) / 2;
  int64_t sum_square = pow(sum, 2);

  int64_t square_sum = 0;
  for (int i = 1; i <= n; i++) {
    square_sum += pow(i, 2);
  }

  std::cout << sum_square - square_sum << "\n";
}

void ith_prime(int n) {

  // A simple guess
  int64_t limit = pow(n, 2);

  std::vector<bool> sieve(limit, true);

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
        std::cout << "The " << prime_count << "th prime is " << i << "\n";
      }
    }
  }
}
