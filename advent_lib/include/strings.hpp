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

} // namespace string
} // namespace advent
