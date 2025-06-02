#include "BigInt.hpp"

bool BigInt::abs_lt(const BigInt::Int &a, const BigInt::Int &b) {
  if (a.size() == b.size()) {
    for (int i = a.size() - 1; 0 <= i; --i) {
      if (a.digit(i) == b.digit(i)) {
        continue;
      } else if (b.digit(i) < a.digit(i)) {
        return false;
      } else {
        return true;
      }
    }
    return false;
  } else {
    return a.size() < b.size();
  }
}

bool BigInt::less_than(const BigInt::Int &a, const BigInt::Int &b) {
  if (!a.sign && b.sign) {
    return true;

  } else if (a.sign && !b.sign) {
    return false;

  } else {
    if (a.size() == b.size()) {
      for (auto it_a = a.begin(), it_b = b.begin(); it_a != a.end();
           ++it_a, ++it_b) {
        if (*it_a == *it_b) {
          continue;
        } else if (*it_a < *it_b) {
          return (a.sign && b.sign) ? true : false;
        } else {
          return false;
        }
      }

      return false;
    } else {
      return a.size() < b.size();
    }
  }
}


bool BigInt::less_than_or_equal(const BigInt::Int &a, const BigInt::Int &b) {
  if (!a.sign && b.sign) {
    return true;

  } else if (a.sign && !b.sign) {
    return false;

  } else {
    if (a.size() == b.size()) {
      for (auto it_a = a.begin(), it_b = b.begin(); it_a != a.end();
           ++it_a, ++it_b) {
        if (*it_a == *it_b) {
          continue;
        } else if (*it_a < *it_b) {
          return (a.sign && b.sign) ? true : false;
        } else {
          return false;
        }
      }

      return true;
    } else {
      return a.size() < b.size();
    }
  }
}
