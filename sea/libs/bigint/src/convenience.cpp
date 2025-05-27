#include "BigInt.hpp"
#include <cstdint>
#include <optional>
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

bool BigInt::Int::leq_int32_sqrt() const {
  static int8_t int64_sqrt_digits[] = {6, 3, 5, 5, 6};

  if (this->size() < 5) {
    return true;
  } else if (this->size() == 5) {

    for (int i = 0; i < 5; ++i) {
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

BigInt::Int BigInt::Int::pow10(size_t n) const {

  BigInt::Int raised(*this);

  if (n == 0) {
    raised.value.clear();
    raised.value.push_back(1);
  } else {

    size_t swap_limit = raised.size();

    for (int i = 0; i < n; ++i) {
      raised.value.push_back(0);
    }

    for (int i = raised.size() - 1; n <= i; --i) {
      raised.value[i] = raised.value[i - n];
    }
    for (int i = 0; i < n; ++i) {
      raised.value[i] = 0;
    }
  }

  raised.strip_leading_zeros();

  return raised;
}

std::pair<std::optional<BigInt::Int>, std::optional<BigInt::Int>>
BigInt::Int::abs_split(size_t pos) const {

  std::optional<BigInt::Int> low = std::nullopt;
  std::optional<BigInt::Int> high = std::nullopt;

  if (pos == 0) {
    high = BigInt::Int(*this);
    goto endsplit;
  }

  {
    size_t i{0};
    low = BigInt::Int();

    for (; i < std::min(pos, this->size()); ++i) {
      low.value().value.push_back(this->digit(i));
    }

    low.value().strip_leading_zeros();

    if (i < this->size()) {
      high = BigInt::Int();
      for (; i < this->size(); ++i) {
        high.value().value.push_back(this->digit(i));
      }
      high.value().strip_leading_zeros();

      goto endsplit;
    }
  }

endsplit:
  return std::make_pair(high, low);
}
