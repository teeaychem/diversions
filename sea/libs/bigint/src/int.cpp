#include "BigInt.hpp"
#include <cstdint>
#include <string>
#include <vector>

BigInt::Int::Int() {
  sign = true;
  value = std::vector<uint8_t>();
}

BigInt::Int::Int(const int64_t &num) {
  BigInt::Int string_helper = BigInt::Int(std::to_string(num));
  value = string_helper.value;
  sign = string_helper.sign;
}

BigInt::Int::Int(const std::string &num) {
  if (num.empty()) {
    throw std::invalid_argument("");
  }

  size_t idx{0};

  sign = true;

  if (!is_digit(*num.begin())) {
    if (num.size() == 1) {
      throw std::invalid_argument("");
    }
    idx++;
    char num_sign = *num.begin();

    if (num_sign == '-' || num_sign == '+') {
      sign = (num_sign == '+' ? true : false);
    } else {
      throw std::invalid_argument("");
    }
  }

  value.reserve(num.size() - idx);

  for (auto it = num.rbegin(); it != num.rend() - idx; it++) {
    if (is_digit(*it)) {
      value.push_back(char_to_digit(*it));
    } else {
      throw std::invalid_argument("");
    }
  }
}

BigInt::Int::Int(const Int &big_int) {
  sign = big_int.sign;
  value = big_int.value;
}

std::ostream &BigInt::operator<<(std::ostream &out, const BigInt::Int &num) {
  if (!(num.sign)) {
    out << '-';
  }

  for (auto it = num.value.rbegin(); it != num.value.rend(); ++it) {
    out << digit_to_char(*it);
  }

  return out;
}
