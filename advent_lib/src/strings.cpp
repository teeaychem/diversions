#include <string>
#include <vector>

namespace advent {
namespace string {

std::vector<std::string> string_split_delim(std::string input,
                                            std::string delimiter) {
  std::vector<std::string> split{};

  size_t pos = 0;
  while ((pos = input.find(delimiter)) != std::string::npos) {
    split.push_back(input.substr(0, pos));
    input.erase(0, pos + delimiter.length());
  }
  split.push_back(input);

  return split;
}

} // namespace string_lib
} // namespace aoc
