#include <BigInt.hpp>
#include <iostream>

using namespace std;

void factorial_digit_sum() {
  BigInt::Int factorial = BigInt::Int(1);

  for (int64_t i = 2; i <= 100; ++i) {

    factorial = factorial * BigInt::Int(i);
  }

  cout << factorial << "\n";

  BigInt::Int sum(0);

  for (auto it = factorial.begin(); it != factorial.end(); ++it) {
    sum = sum + BigInt::Int(*it);
  }

  cout << sum << "\n";
}
