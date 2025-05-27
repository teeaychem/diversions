#pragma once

#include <cstdint>
#include <iostream>
#include <optional>
#include <string>
#include <sys/types.h>
#include <vector>

namespace BigInt {

class Int {
  // Sign is true if position, false if negative.
  bool sign;
  // Digits are stored as uint_t in reverse order.
  std::vector<uint8_t> value;

  // Convenience
  void strip_leading_zeros();
  bool leq_int64_sqrt() const;
  bool leq_int32_sqrt() const;

public:
  // Convenience
  inline size_t size() const { return this->value.size(); };
  inline uint8_t digit(size_t i) const { return this->value.at(i); };
  inline bool is_zero() const {
    return this->value.size() == 1 && this->value.at(0) == 0;
  };

  bool is_powerof10() const;
  Int pow10(size_t) const;

  inline std::vector<uint8_t>::const_reverse_iterator begin() const {
    return this->value.crbegin();
  };

  inline std::vector<uint8_t>::const_reverse_iterator end() const {
    return this->value.crend();
  };

  std::pair<std::optional<Int>, std::optional<Int>> abs_split(size_t pos) const;

  // Streams:
  friend std::ostream &operator<<(std::ostream &, const Int &);

  // Unary ops
  Int();
  Int(const std::string &);
  Int(const int64_t &);
  Int(const Int &);

  // Binary ops

  // Standalone friends
  friend Int add(const BigInt::Int &a, const BigInt::Int &b);
  friend Int subtract(const BigInt::Int &a, const BigInt::Int &b);
  friend Int multiply(const BigInt::Int &a, const BigInt::Int &b);

  // Overloads
  inline Int operator-() const;

  inline Int operator+(const Int &num) const { return add(*this, num); };
  inline Int operator-(const Int &num) const { return subtract(*this, num); };
  inline Int operator*(const Int &num) const { return multiply(*this, num); };

  // Comparisons

  // Standalone friends
  friend bool leq(const BigInt::Int &a, const BigInt::Int &b);

  // Overloads
  inline bool operator==(const Int &num) const {
    return (sign == num.sign) && (value == num.value);
  };

  // Coversion
  std::string to_istring() const;
  std::optional<int64_t> try_int64() const;
};

} // namespace BigInt

namespace BigInt {

// Conveniece
inline bool is_digit(char c) { return ('0' <= c && c <= '9'); };
inline uint8_t char_to_digit(char c) { return c - '0'; };
inline char digit_to_char(uint8_t d) { return d + '0'; };

// Standalone friends
Int add(const BigInt::Int &a, const BigInt::Int &b);
Int subtract(const BigInt::Int &a, const BigInt::Int &b);
Int multiply(const BigInt::Int &a, const BigInt::Int &b);

bool abs_lt(const BigInt::Int &a, const BigInt::Int &b);

} // namespace BigInt
