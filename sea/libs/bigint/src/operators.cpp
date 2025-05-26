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
    BigInt::Int c = b;
    c.sign = true;

    return BigInt::subtract(a, c);
  } else if (!a.sign && b.sign) {
    BigInt::Int c = a;
    c.sign = true;

    c = BigInt::subtract(c, b);
    c.sign = false;

    return c;
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

  Int result = BigInt::Int();

  bool a_leq_b = leq(a, b);

  const BigInt::Int &l = a_leq_b ? a : b;
  BigInt::Int h = a_leq_b ? b : a;

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

  if (!result.is_zero()) {
    result.sign = !a_leq_b;
  }

  return result;
}

// Karatsuba with int64_t base case.
BigInt::Int BigInt::multiply(const BigInt::Int &a, const BigInt::Int &b) {

  // Base case.
  if (a.leq_int64_sqrt() && b.leq_int64_sqrt()) {
    // a[b] ≤ sqrt(int64_max) and so the try succeeds.
    int64_t a64 = a.try_int64().value();
    int64_t b64 = b.try_int64().value();
    return BigInt::Int(std::to_string(a64 * b64));
  }

  // Recursive case.
  size_t split_pos = std::max(a.size(), b.size()) / 2;
  size_t split_pow = ceil(std::max(a.size(), b.size()) / 2.0);

  auto [a_high, a_low] = a.split(split_pos);
  auto [b_high, b_low] = b.split(split_pos);

  auto z_high = (a_high * b_high);
  auto z_low = (a_low * b_low);

  auto z_mid = (((a_high + a_low) * (b_high + b_low)) - (z_high + z_low));

  z_high.pow10(2 * split_pow);
  z_mid.pow10(split_pow);

  auto z = ((z_high + z_mid) + z_low);

  if (a.sign == b.sign) {
    z.sign = true;
  } else {
    z.sign = false;
  }

  return z;
}
