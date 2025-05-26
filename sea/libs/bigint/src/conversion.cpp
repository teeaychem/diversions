
#include "BigInt.hpp"
#include <cassert>
#include <cmath>
#include <optional>
#include <string>

std::string BigInt::Int::to_istring() const {
  std::string out_str{};
  out_str.reserve(value.size());
  if (!sign) {
    out_str.push_back('-');
  }

  for (auto it = value.rbegin(); it != value.rend(); ++it) {
    out_str.push_back(digit_to_char(*it));
  }

  return out_str;
}

std::optional<int64_t> BigInt::Int::try_int64() const {
  static uint8_t int64_digits[] = {7, 0, 8, 5, 7, 7, 4, 5, 8, 6,
                                   3, 0, 2, 7, 3, 3, 2, 2, 9};

  int64_t result{0};

  if (this->size() < 19) {
    for (int i = 0; i < this->size(); ++i) {
      result += (this->digit(i) * (pow(10, i)));
    }
  } else if (this->size() == 19) {
    for (int i = 0; i < 19; ++i) {
      if (this->digit(i) <= int64_digits[i]) {
        result += (this->digit(i) * (pow(10, i)));
      } else {
        return std::nullopt;
      }
    }
  }

  result *= this->sign ? 1 : -1;

  return result;
}
