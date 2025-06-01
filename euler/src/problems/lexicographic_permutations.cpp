#include "utils/utils.hpp"
#include "utils/display.hpp"
#include <cstdint>
#include <vector>

void lexicographic_permutations() {
  size_t count{999999};
  std::vector<int64_t> digits{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

  for (size_t i{0}; i < count; ++i) {
    euler::utils::next_permutation(digits);
  }

  euler::display::cout_vector(digits, "");
};
