#include <BigInt.hpp>

void power_digit_sum() {
  BigInt::Int power_digits(2);

  for (size_t i{2}; i <= 1000; ++i) {
    power_digits = power_digits * BigInt::Int(2);
  }

  BigInt::Int sum = BigInt::Int(0);

  for (auto it = power_digits.begin(); it != power_digits.end(); ++it) {
    sum = sum + *it;
  }

  std::cout << sum << "\n";
}
