#include <fstream>
#include <iostream>
#include <ostream>
#include <string>

using namespace std;

bool vowel(char c) {
  static string vowels = "aeiou";
  return (vowels.find(c) != string::npos);
}

bool bad_pair(char a, char b) {
  return (a == 'a' && b == 'b') || (a == 'c' && b == 'd') ||
         (a == 'p' && b == 'q') || (a == 'x' && b == 'y');
}

bool evaluate_one(string the_string) {
  if (the_string.size() < 2) {
    return false;
  }

  char last = the_string[0];
  int vowel_count = vowel(last) ? 1 : 0;
  int twice_count = 0;
  for (size_t i = 1; i < the_string.size(); i++) {
    char current = the_string[i];
    if (vowel(current)) {
      vowel_count += 1;
    }
    if (last == current) {
      twice_count += 1;
    }
    if (bad_pair(last, current)) {
      return false;
    } else {
      last = current;
    }
  }
  return (vowel_count > 2 && twice_count > 0);
}

bool evaluate_two(string the_string) {
  if (the_string.size() < 2) {
    return false;
  }

  char last = the_string[0];
  int pair_count = 0;
  int one_degree_count = 0;
  for (size_t i = 1; i < the_string.size() - 1; i++) {
    char current = the_string[i];
    if (the_string[i + 1] == last) {
      one_degree_count += 1;
    }
    for (size_t j = i + 1; j < the_string.size(); j++) {
      if (the_string[j] == last && the_string[j + 1] == current) {
        pair_count += 1;
      }
    }

    last = current;
  }
  return (pair_count > 0 && one_degree_count > 0);
}

int main(int argc, char **argv) {

  auto nice_tests = {"ugknbfddgicrmopn", "jchzalrnumimnmhp", "haegwjzuvuyypxyu",
                     "dvszwmarrgswjxmb"};

  for (string test : nice_tests) {
    cout << evaluate_one(test) << endl;
  }

  auto second_nice_tests = {"qjhvhtzxzqqjkmpb", "uurcxstgmygtbstg",
                            "ieodomkazucvgmuy"};

  for (string test : second_nice_tests) {
    cout << evaluate_two(test) << endl;
  }

  if (argc != 2) {
    cout << "A file is needed for anything else…" << endl;
    exit(0);
  }

  string the_file = argv[1];
  std::ifstream infile(the_file);

  std::string line;

  int nice_count = 0;
  int second_nice_count = 0;

  for (std::string line; getline(infile, line);) {
    if (evaluate_one(line)) {
      nice_count += 1;
    }
    if (evaluate_two(line)) {
      second_nice_count += 1;
    }
  }

  cout << "Nice count: " << nice_count << endl;
  cout << "Second nice count: " << second_nice_count << endl;

  return 0;
}
