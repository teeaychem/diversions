#include <optional>
#include <string>
#include <vector>

namespace advent {
namespace string {

std::vector<std::string> string_split_delim(std::string input,
                                            std::string delimiter);

template <typename element>
std::string join(const element &v, const std::string &delimiter) {
  std::string s{};
  for (auto &e : v) {
    if (e != v[0]) {
      s += delimiter;
    }
    s += e;
  }
  return s;
}

std::optional<char> first_consecutive_char(std::string s, size_t i) {
  for (size_t j = 0; j <= (s.size() - i); j++) {
    std::optional<char> same = s[j];
    for (size_t ii = 0; ii < i; ii++) {
      if (s[j] != s[j + ii]) {
        same = std::nullopt;
      }
    }
    if (same.has_value()) {
      return same;
    }
  }
  return std::nullopt;
}

bool in_a_row(std::string s, size_t i) {
  for (size_t j = 0; j <= (s.size() - i); j++) {
    bool same = true;
    for (size_t ii = 0; ii < i; ii++) {
      if (s[j] != s[j + ii]) {
        same = false;
      }
    }
    if (same) {
      return true;
    }
  }
  return false;
}

bool c_in_a_row(std::string s, char c, size_t i) {
  for (size_t j = 0; j <= (s.size() - i); j++) {
    if (s[j] == c) {
      bool same = true;
      for (size_t ii = 0; ii < i; ii++) {
        if (s[j] != s[j + ii]) {
          same = false;
        }
      }
      if (same) {
        return true;
      }
    }
  }
  return false;
}

} // namespace string
} // namespace advent
