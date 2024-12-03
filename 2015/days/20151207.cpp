#include <cstdint>
#include <fstream>
#include <iostream>
#include <map>
#include <ostream>
#include <queue>
#include <regex>
#include <string>

using namespace std;

using wire_map = map<string, uint16_t>;

bool parse(wire_map *wm, string action) {
  // cout << "parsing: " << action << endl;

  regex signal_regex("(\\d+|[a-z]+) -> ([a-z]+)");
  smatch signal_matches;
  regex_match(action, signal_matches, signal_regex);
  if (!signal_matches.empty()) {
    string match_one = signal_matches[1];
    uint16_t signal;
    try {
      signal = (uint16_t)stoi(match_one);
    } catch (exception &errk) {
      if (wm->contains(match_one)) {
        signal = wm->at(match_one);
      } else {
        return false;
      }
    }

    string destinaton = signal_matches[2];
    // cout << signal << " -> " << destinaton << endl;
    wm->emplace(destinaton, signal);
    return true;
  }

  regex unary_regex("NOT ([a-z]+) -> ([a-z]+)");
  smatch unary_matches;
  regex_match(action, unary_matches, unary_regex);
  if (!unary_matches.empty()) {
    string source = unary_matches[1];
    string destinaton = unary_matches[2];
    if (wm->contains(source)) {
      uint16_t signal = ~(wm->at(source));
      wm->emplace(destinaton, signal);
      return true;
    } else {
      return false;
    }
  }

  regex binary_regex("([a-z]+|\\d+) (AND|OR) ([a-z]+|\\d+) -> ([a-z]+)");
  smatch binary_matches;
  regex_match(action, binary_matches, binary_regex);
  if (!binary_matches.empty()) {
    string operation = binary_matches[2];
    string source_l = binary_matches[1];
    string source_r = binary_matches[3];
    string destinaton = binary_matches[4];
    // cout << source_l << " " << operation << " " << source_r << " -> "
    // << destinaton << endl;
    uint16_t wm_l;
    try {
      wm_l = (uint16_t)stoi(source_l);
    } catch (exception &errk) {
      if (wm->contains(source_l)) {
        wm_l = wm->at(source_l);
      } else {
        return false;
      }
    }
    uint16_t wm_r;
    try {
      wm_r = (uint16_t)stoi(source_r);
    } catch (exception &errk) {
      if (wm->contains(source_r)) {
        wm_r = wm->at(source_r);
      } else {
        return false;
      }
    }

    uint16_t signal;
    if (operation == "AND") {
      signal = wm_l & wm_r;
    } else if (operation == "OR") {
      signal = wm_l | wm_r;
    } else {
      cout << "Unknown binary op: " << operation << endl;
      exit(1);
    }
    wm->emplace(destinaton, signal);
    return true;
  }

  regex shift_regex("([a-z]+|\\d+) (LSHIFT|RSHIFT) (\\d+) -> ([a-z]+)");
  smatch shift_matches;
  regex_match(action, shift_matches, shift_regex);
  if (!shift_matches.empty()) {
    string source = shift_matches[1];
    string shift = shift_matches[2];
    int amount = stoi(shift_matches[3]);
    string destinaton = shift_matches[4];
    // cout << source << " " << shift << " " << amount << " -> " << destinaton
    //      << endl;

    uint16_t signal;
    try {
      signal = (uint16_t)stoi(source);
    } catch (exception &errk) {
      if (wm->contains(source)) {
        signal = wm->at(source);
      } else {
        return false;
      }
    }

    if (shift == "LSHIFT") {
      signal = wm->at(source) << amount;
    } else if (shift == "RSHIFT") {
      signal = wm->at(source) >> amount;
    } else {
      cout << "Unknown binary op: " << shift << endl;
      exit(1);
    }
    wm->emplace(destinaton, signal);
    return true;
  }
  cout << "Missed: " << action << endl;
  exit(1);
}

int main(int argc, char **argv) {

  bool test = false;
  if (test) {

    wire_map wm_test;
    vector<string> actions = {
        "123 -> x",    "456 -> y",        "x AND y -> d",
        "x OR y -> e", "x LSHIFT 2 -> f", "y RSHIFT 2 -> g",
        "NOT x -> h",  "NOT y -> i"

    };
    for (string action : actions) {
      parse(&wm_test, action);
    }

    for (auto kv : wm_test) {
      cout << kv.first << " " << kv.second << endl;
    }
  }

  wire_map wm;

  string the_file = argv[1];
  std::ifstream infile(the_file);

  std::string line;

  queue<string> line_queue{};

  for (std::string line; getline(infile, line);) {
    line_queue.push(line);
  }
  while (!line_queue.empty()) {
    string line = line_queue.front();
    line_queue.pop();
    if (!parse(&wm, line)) {
      line_queue.push(line);
    }
  }

  // for (auto kv : wm) {
  //   cout << kv.first << " " << kv.second << endl;
  // }

  cout << wm.at("a") << endl;

  return 0;
}
