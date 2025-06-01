#include <iostream>

namespace euler {
namespace display {
template <typename T>
inline void cout_vector(std::vector<T> &v, std::string sep) {
  for (auto e : v) {
    std::cout << e << sep;
  }
  std::cout << "\n";
}

template <typename T>
inline void cout_pairs_vector(std::vector<std::pair<T, T>> &v,
                              std::string sep) {
  for (auto e : v) {
    std::cout << e.first << "·" << e.second << sep;
  }
  std::cout << "\n";
}

} // namespace display
} // namespace euler
