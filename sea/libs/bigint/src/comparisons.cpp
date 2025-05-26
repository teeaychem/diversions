#include "BigInt.hpp"

bool BigInt::leq(const BigInt::Int &a, const BigInt::Int &b) {
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
    return true;
  } else {
    return a.size() < b.size();
  }
}
