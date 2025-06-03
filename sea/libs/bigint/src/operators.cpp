#include "BigInt.hpp"
#include <cstdint>
#include <string>

// Unary

BigInt::Int BigInt::Int::operator-() const {
  BigInt::Int fresh(*this);
  if (!fresh.is_zero()) {
    fresh.sign = !fresh.sign;
  }

  return fresh;
};

// Binary

BigInt::Int BigInt::add(const BigInt::Int &a, const BigInt::Int &b) {

  if (a.sign && !b.sign) {
    return (a - -b);
  } else if (!a.sign && b.sign) {
    return b - -a;
  }

  Int result = BigInt::Int();

  bool a_smol_b = a.size() <= b.size();

  const BigInt::Int &l = a_smol_b ? a : b;
  const BigInt::Int &h = a_smol_b ? b : a;

  uint8_t carry{0};
  uint8_t sum{0};

  int i{0};

  // Work through l and h until l is exhausted.
  for (; i < l.size(); ++i) {
    sum = l.digit(i) + h.digit(i) + carry;
    result.value.push_back(sum % 10);
    carry = sum / 10;
  }

  // Work through h.
  for (; i < h.size(); ++i) {
    sum = h.digit(i) + carry;
    result.value.push_back(sum % 10);
    carry = sum / 10;
  }

  if (carry != 0) {
    result.value.push_back(carry);
  }

  return result;
}

BigInt::Int BigInt::subtract(const BigInt::Int &a, const BigInt::Int &b) {

  if (a.sign && !b.sign) {
    return (a + -b);
  }

  if (!a.sign && b.sign) {
    return -(-a + b);
  }

  Int result = BigInt::Int();

  bool a_abs_lt_b = abs_lt(a, b);

  const BigInt::Int &l = a_abs_lt_b ? a : b;
  BigInt::Int h = a_abs_lt_b ? b : a;

  if ((a_abs_lt_b && b.sign) || (!b.sign)) {
    result.sign = false;
  }

  for (int i = 0; i < h.size(); ++i) {
    if (l.size() <= i) {
      result.value.push_back(h.digit(i));
    } else {
      // Regoup.
      if (h.digit(i) < l.digit(i)) {
        // As l < h there must be some non-zero digit to the right of i.
        for (int j = i + 1; j < h.size(); j++) {
          if (h.digit(j) != 0) {
            h.value[j--]--;
            // Range (ith, non-zero): Directly borrow 9 as the digit was 0.
            while (i < j) {
              h.value[j--] = 9;
            }
            // For the ith digit, borrow 10.
            h.value[i] += 10;

            break;
          }
        }
      }

      h.value[i] -= l.value[i];

      result.value.push_back(h.digit(i));
    }
  }

  result.strip_leading_zeros();

  if (result.is_zero()) {
    result.sign = true;
  }

  return result;
}

// Karatsuba with sqrt(int64_t::MAX) base case.
BigInt::Int BigInt::multiply(const BigInt::Int &a, const BigInt::Int &b) {

  if (a.is_zero() || b.is_zero()) {
    return BigInt::Int(0);
  }

  // Base case.

  if (a.leq_int64_sqrt() && b.leq_int64_sqrt()) {
    // a, b ≤ sqrt(int64_max) and so the try succeeds.
    int64_t a64 = a.try_int64().value();
    int64_t b64 = b.try_int64().value();

    return BigInt::Int(std::to_string(a64 * b64));
  }

  // Recursive case.

  size_t split_pow = std::max(a.size(), b.size()) / 2;

  auto [a_high, a_low] = a.abs_split(split_pow);
  auto [b_high, b_low] = b.abs_split(split_pow);

  auto a_high_val = a_high.value_or(BigInt::Int(0));
  auto a_low_val = a_low.value_or(BigInt::Int(0));
  auto b_high_val = b_high.value_or(BigInt::Int(0));
  auto b_low_val = b_low.value_or(BigInt::Int(0));

  auto z_high = (a_high_val * b_high_val);
  auto z_low = (a_low_val * b_low_val);

  auto a_sum = (a_high_val + a_low_val);
  auto b_sum = (b_low_val + b_high_val);

  auto z_sum_mul = (a_sum * b_sum);

  auto z_mid = (z_sum_mul - z_high - z_low);

  auto z_high_pow = z_high.pow10(2 * split_pow);
  auto z_mid_pow = z_mid.pow10(split_pow);

  BigInt::Int z = ((z_high_pow + z_mid_pow) + z_low);

  z.sign = (a.sign == b.sign);

  return z;
}

BigInt::Int BigInt::pow(const BigInt::Int &a, const BigInt::Int &b) {

  if (b.is_zero()) {
    return BigInt::Int{1};
  }

  BigInt::Int raised{a};

  for (BigInt::Int i{1}; i < b; i = i + 1) {

    raised = raised * a;
  }

  return raised;
}

BigInt::Int BigInt::factorial(const BigInt::Int &a) {

  if (a.is_zero()) {
    return BigInt::Int{1};
  }

  BigInt::Int total{1};

  for (BigInt::Int i{1}; i <= a; i = i + 1) {

    total = total * i;
  }

  return total;
}
