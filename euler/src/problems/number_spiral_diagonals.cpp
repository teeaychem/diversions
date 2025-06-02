#include "utils/display.hpp"
#include <cstdint>

/*
  The spiral can be seen as nested sqaures.
  Handle the first square ([1]) as a special case.
  Each subsequent square starts from the last number in the previous square.
  Each diagonal is found at fixed offsets corresponding to the length of edges.
 */
void number_spiral_diagonals() {

  int64_t size{1001};

  int64_t diagonal_sum{1};

  int64_t start{1};
  for (int64_t square{3}; square <= size; square += 2) {
    int64_t offset = square - 1;

    for (int64_t m{1}; m <= 4; ++m) {
      diagonal_sum += start + (m * offset);
    }

    start += (4 * offset);
  }

  std::cout << diagonal_sum << "\n";
}
