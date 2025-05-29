#include <cstdint>
namespace euler {
namespace utils {
inline uint64_t proper_divisor_sum(uint64_t n) {
  uint64_t divisor_sum{0};
  for (uint64_t divisor{0}; divisor < n; ++divisor) {
    if (n % divisor == 0) {
      divisor_sum += divisor;
    }
  }

  return divisor_sum;
}

} // namespace utils
} // namespace euler
