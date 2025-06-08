
#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <vector>
int64_t ith_pentagonal(int64_t i) {
  return i * (3 * i - 1) / 2;
}

void pentagon_numbers() {

  std::vector<int64_t> pentagonals{};
  std::vector<int64_t> sums{};

  int64_t i{3};

  for (int64_t i{1}; i < pow(2, 20); ++i) {
    pentagonals.push_back(ith_pentagonal(i));
  }

  std::cout << "Pentagonals set" << "\n";

  for (size_t x{0}; x < std::min(pentagonals.size(), (size_t)10); ++x) {
    std::cout << pentagonals[x] << "\n";
  }

  for (size_t x{0}; x < pentagonals.size(); ++x) {

    int64_t a = pentagonals[x];

    for (size_t y{x}; y < pentagonals.size(); ++y) {

      int64_t b = pentagonals[y];

      bool d_ok = std::binary_search(pentagonals.begin(), pentagonals.end(), b - a);

      if (d_ok) {
        bool s_ok = std::binary_search(pentagonals.begin(), pentagonals.end(),
                                       b + a);

        if (s_ok) {
          std::cout << a << " " << b << " Difference: " << b - a << "\n";
          return;
        }
      }
    }
  }
};
