#include <cstdint>
#include <iostream>
#include <set>

/*
  Consider possible products and do pair factorisation to check for pandigitality.

A key observation is that the product has at most four digits, as to create a five digit product would require five digits.

To help with efficiency, pandigitality is checked by setting flags for each digit.
And, a check is made to ensure 0 is not found when setting a flag.
 */
void pandigital_products() {

  bool digit_flags[10]; // ignore index 0 to avoid calculaitng offsets.
  std::set<int64_t> products{};

  auto clear_digit_flags = [&digit_flags]() {
    for (int64_t d{0}; d < 10; ++d) {
      digit_flags[d] = false;
    }
  };

  auto check_digits = [&digit_flags]() {
    for (int64_t d{1}; d < 10; ++d) {
      if (!digit_flags[d]) {
        return false;
      };
    }

    return true;
  };

  auto set_digit_flag = [&digit_flags](int64_t n) {
    while (n != 0) {
      int64_t m{n % 10};

      if (m == 0 || digit_flags[m]) {
        return false;
      }

      digit_flags[m] = true;
      n /= 10;
    }

    return true;
  };

  clear_digit_flags();

  // get product
  for (int64_t product{1}; product < 10000; ++product) {
    // consider possible factors
    for (int64_t factor{2}; factor * factor <= product; ++factor) {
      // for each factor
      if (product % factor == 0) {
        // check each component has unique digits
        if (set_digit_flag(product) && set_digit_flag(factor) &&
            set_digit_flag(product / factor)) {
          // ensure all digits are covered
          if (check_digits()) {
            // std::cout << factor << " * " << product / factor << " = " << product << "\n";
            products.insert(product);
          }
        }

        clear_digit_flags();
      }
    }
  }

  int64_t sum{0};
  for (int64_t product : products) {
    sum += product;
  }

  std::cout << "Product sum: " << sum << "\n";
}
