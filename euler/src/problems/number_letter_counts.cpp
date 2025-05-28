#include <cstdint>
#include <iostream>
#include <vector>

std::string itos(int i) {

  static std::vector<std::string> below_twenty{
      "zero",    "one",     "two",       "three",    "four",
      "five",    "six",     "seven",     "eight",    "nine",
      "ten",     "eleven",  "twelve",    "thirteen", "fourteen",
      "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"};

  static std::vector<std::string> tens{"",      "",     "twenty", "thirty",
                                       "forty",  "fifty", "sixty",  "seventy",
                                       "eighty", "ninety"};

  if (0 <= i && i < 20) {
    return below_twenty.at(i);
  }

  else if (20 <= i && i < 100) {
    std::string out_string{};
    out_string.append(tens.at(i / 10));
    if (i % 10 != 0) {
      out_string.append(below_twenty.at(i % 10));
    }

    return out_string;
  }

  else if (100 <= i && i < 1000) {
    std::string out_string{};
    out_string.append(below_twenty.at(i / 100));
    out_string.append("hundred");

    if (i % 100 != 0) {
      out_string.append("and");
      out_string.append(itos(i % 100));
    }

    return out_string;
  }

  else if (i == 1000) {
    return "onethousand";
  }

  else {
    std::cout << "too high!" << "\n";
    return "!";
  }
}

void number_letter_counts() {
  int64_t letters_used{0};
  for (int i{1}; i <= 1000; ++i) {
    letters_used += itos(i).size();
  }

  std::cout << "Lettters used: " << letters_used << "\n";
};
