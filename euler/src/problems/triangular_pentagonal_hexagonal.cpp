

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <iterator>
#include <vector>

void triangular_pentagonal_hexagonal() {

  std::vector<int64_t> triangle{};
  std::vector<int64_t> pentagonal{};
  std::vector<int64_t> hexagonal{};

  int64_t limit = pow(2, 20);

  for (int64_t i{1}; i < limit; ++i) {
    triangle.push_back((i * (i + 1)) / 2);
    pentagonal.push_back((i * (3 * i - 1)) / 2);
    hexagonal.push_back((i * (2 * i - 1)));
  }

  std::vector<int64_t> tp{};

  auto x = std::set_intersection(triangle.begin(), triangle.end(),
                                 pentagonal.begin(), pentagonal.end(),
                                 std::back_inserter(tp));

  for (auto h : hexagonal) {
    if (std::binary_search(tp.begin(), tp.end(), h)) {
      std::cout << h << "\n";
    }
  }
}
