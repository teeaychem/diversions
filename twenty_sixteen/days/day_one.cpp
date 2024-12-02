
#include <advent/location.hpp>
#include <cstdio>
#include <format>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <unordered_set>
using namespace std;

void process_instructions(string i) {
  unordered_set<string> visited{};
  advent::location::coordinate l = pair(0, 0);
  visited.insert(advent::location::location_string(l));
  advent::location::direction facing = advent::location::direction::up;

  regex instruction_regex("((?:L|R)\\d+)");
  smatch instruction_math;

  regex_token_iterator<string::iterator> regex_end;
  regex_token_iterator<string::iterator> instructions(i.begin(), i.end(),
                                                      instruction_regex);

  string l_s;
  auto update = [&l, &l_s, &visited]() {
    l_s = advent::location::location_string(l);
    if (visited.contains(l_s)) {
      cout << advent::location::location_string(l) << endl;
      cout << abs(l.first) + abs(l.second) << endl;
      return true;
    } else {
      visited.insert(l_s);
      return false;
    }
  };

  while (instructions != regex_end) {
    string instruction = *instructions;

    if (instruction[0] == 'L') {
      facing = rotate_left(facing);
    } else if (instruction[0] == 'R') {
      facing = rotate_right(facing);
    }

    int steps = stoi(instruction.substr(1, instruction.size()));
    switch (facing) {
    case advent::location::direction::up:
      for (int i = 1; i <= steps; i++) {
        l.second += 1;
        if (update()) {
          return;
        };
      }
      break;
    case advent::location::direction::down:
      for (int i = 1; i <= steps; i++) {
        l.second -= 1;
        if (update()) {
          return;
        };
      }
      break;

    case advent::location::direction::left:
      for (int i = 1; i <= steps; i++) {
        l.first -= 1;
        if (update()) {
          return;
        };
      }
      break;

    case advent::location::direction::right:
      for (int i = 1; i <= steps; i++) {
        l.first += 1;
        if (update()) {
          return;
        };
      }
      break;
    }

    instructions++;
  }
  cout << advent::location::location_string(l) << endl;
  cout << abs(l.first) + abs(l.second) << endl;
}

int main(int argc, char **argv) {

  // process_instructions("R2, L3");
  // process_instructions("R2, R2, R2");
  // process_instructions("R5, L5, R5, R3");
  // process_instructions("R8, R4, R4, R8");

  ifstream infile(argv[1]);
  string all_instructions{};
  for (string line; getline(infile, line);) {
    all_instructions.append(line);
  }

  process_instructions(all_instructions);
  return 0;
}
