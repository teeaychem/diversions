#include <cstdint>
#include <vector>
namespace euler {
namespace utils {

template <typename T> void next_permutation(std::vector<T> &v) {
  size_t size = v.size();

  size_t pivot{size - 2};

  for (auto it = v.rbegin() + 1; it != v.rend(); ++it) {
    if (*it < *(it - 1)) {
      goto use_pivot;
    } else {
      --pivot;
    }
  }

reverse:

  std::reverse(v.begin(), v.end());
  return;

use_pivot:

  size_t until_pivot = size - 1 - pivot;
  T pivot_value = v.at(pivot);

  for (auto it = v.rbegin(); it != v.rend() && 0 < until_pivot; ++it) {
    if (pivot_value < *it) {
      std::swap(v.at(pivot), *it);
      break;
    }

    --until_pivot;
  }

  std::reverse(v.begin() + pivot + 1, v.end());
  return;
}

} // namespace utils
} // namespace euler
