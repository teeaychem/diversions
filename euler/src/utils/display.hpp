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
} // namespace display
} // namespace euler
