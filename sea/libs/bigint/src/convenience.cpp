#include "BigInt.hpp"
#include <cstdint>
#include <utility>

// Private

void BigInt::Int::strip_leading_zeros() {
  while (1 < this->value.size() && this->value.back() == 0) {
    this->value.pop_back();
  }
}

bool BigInt::Int::leq_int64_sqrt() const {
  static int8_t int64_sqrt_digits[] = {9, 9, 4, 0, 0, 0, 7, 3, 0, 3};

  if (this->size() < 10) {
    return true;
  } else if (this->size() == 10) {

    for (int i = 0; i < 10; ++i) {
      if (int64_sqrt_digits[i] < this->digit(i)) {
        return false;
      }
    }
    return true;
  } else {
    return false;
  }
}

// Public

bool BigInt::Int::is_powerof10() const {
  if (this->value.empty() || this->value.back() != 1) {
    return false;
  }

  for (size_t i = this->value.size() - 2; 0 < i; --i) {
    if (this->digit(i) != 0) {
      return false;
    }
  }

  return true;
}

BigInt::Int BigInt::Int::pow10(size_t n) {
  if (n == 0) {
    this->value.clear();
    this->value.push_back(1);
  } else {

    size_t swap_limit = this->size();

    for (int i = 0; i < n; ++i) {
      this->value.push_back(0);
    }

    for (int i = this->size() - 1; n <= i; --i) {
      this->value[i] = this->value[i - n];
    }
    for (int i = 0; i < n; ++i) {
      this->value[i] = 0;
    }
  }

  return *this;
}

std::pair<BigInt::Int, BigInt::Int> BigInt::Int::split(size_t pos) const {

  BigInt::Int high{};
  BigInt::Int low{};

  size_t i{0};

  for (; i < pos; ++i) {
    low.value.push_back(this->digit(i));
  }

  if (i < this->size()) {
    for (; i < this->size(); ++i) {
      high.value.push_back(this->digit(i));
    }
  } else {
    high.value.push_back(0);
  }

  return std::make_pair(high, low);
}
