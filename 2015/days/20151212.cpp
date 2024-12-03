#include <cstddef>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <regex>
#include <string>

using namespace std;
using json = nlohmann::json;

int digit_count(string file) {
  regex_token_iterator<string::iterator> string_end;
  regex number_regex("(-?\\d+)");

  int total{0};

  ifstream infile(file);

  for (string line; getline(infile, line);) {

    regex_token_iterator<string::iterator> numbers(line.begin(), line.end(),
                                                   number_regex);
    while (numbers != string_end) {
      total += stoi(*numbers++);
    }
  }
  return total;
}

int get_the_thing(json element) {

  if (element.is_string()) {
    return 0;
  }
  if (element.is_number_integer()) {
    return element;
  }

  if (element.is_array()) {
    int array_total{0};
    for (auto array_element : element) {
      int value = get_the_thing(array_element);
      array_total += value;
    }
    return array_total;
  }

  if (element.is_object()) {
    if (element.contains("red")) {
      return 0;
    } else {
      int object_total{0};
      for (auto &[key, value] : element.items()) {
        if (value.is_string()) {
          string x = value;
          if (x == "red") {
            return 0;
          }
        }

        object_total += get_the_thing(value);
      }
      return object_total;
    }
  }

  cout << "x_x" << endl;
  exit(1);

  return 0;
}

int main(int argc, char **argv) {

  if (argc != 2) {
    cout << "A file is needed for anything else…" << endl;
    exit(0);
  }

  cout << digit_count(argv[1]) << endl;

  std::ifstream f(argv[1]);
  json data = json::parse(f);
  cout << get_the_thing(data) << endl;

  return 0;
}
