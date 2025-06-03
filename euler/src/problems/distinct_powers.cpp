#include <BigInt.hpp>
#include <iostream>
#include <set>

void distinct_powers() {

  std::cout << "distinct_powers" << std::endl;

  std::set<BigInt::Int> powers{};

  BigInt::Int limit{100};

  for (BigInt::Int a{2}; a <= limit; a = a + 1) {
    for (BigInt::Int b{2}; b <= limit; b = b + 1) {
      std::cout << a << "^" << b << " -> " << std::endl;
      BigInt::Int raised{pow(a, b)};
      powers.insert(raised);
      std::cout << "\t" << raised << "\n";
    }
  }

  std::cout << powers.size() << "\n";
}
