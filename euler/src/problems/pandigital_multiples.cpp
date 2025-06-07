#include "utils/utils.hpp"
#include <cstdint>
#include <iostream>

void pandigital_multiples() {

  std::vector<bool> digits = std::vector(10, false);

  auto clear_digits = [&digits]() {
    for (size_t i{1}; i <= 10; ++i) {
      digits[i] = false;
    }
  };

  auto mark_digits = [&digits](int64_t n) -> size_t {
    size_t count{0};
    while (n != 0) {
      int64_t d = n % 10;
      if (digits[d]) {
        return 0;
      }
      digits[d] = true;
      count++;
      n /= 10;
    }

    return count;
  };

  int64_t max_pandigital{123456789};

  for (int64_t i{192}; i <= 100000; ++i) {
    clear_digits();

    size_t digit_count{0};
    int64_t m{1};

    for (; m <= 100000; ++m) {
      size_t m_count = mark_digits(m * i);
      digit_count += m_count;
      if (m_count == 0 || digit_count == 9) {
        break;
      }
    }

    if (digit_count == 9) {
      int64_t product{i};
      for (int64_t x{2}; x <= m; ++x) {
        int64_t next = i * x;
        product *= pow(10, euler::utils::count_digits(next));
        product += next;
      }

      max_pandigital = std::max(max_pandigital, product);

      std::cout << i << " " << m << " " << product << "\n";
    }
  }

  std::cout << max_pandigital << "\n";
}
