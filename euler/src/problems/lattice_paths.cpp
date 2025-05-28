#include <cstdint>
#include <iostream>
#include <vector>
void lattice_paths() {

  size_t size = 20;

  std::vector<std::vector<int64_t>> paths =
      std::vector(size + 1, std::vector(size + 1, (int64_t)1));

  for (size_t i{1}; i <= size; ++i) {
    for (size_t j{1}; j <= size; ++j) {
      paths[i][j] = paths[i][j - 1] + paths[i - 1][j];
    }
  }

  for (size_t i{0}; i <= size; ++i) {
    for (size_t j{0}; j <= size; ++j) {
      std::cout << paths[i][j] << " ";
    }
    std::cout << "\n";
  }

  std::cout << paths[size][size] << "\n";
}
