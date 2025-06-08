#include <BigInt.hpp>
#include <cstdint>

void self_powers() {

  BigInt::Int sum{0};


  for (int64_t i{1}; i <= 1000; ++i) {
    sum = sum + BigInt::pow(BigInt::Int{i}, BigInt::Int{i});
    std::cout << sum << "\n";
  }

  std::cout << sum << "\n";

};
