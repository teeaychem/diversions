#include <iostream>
#include <optional>
#include <ostream>
#include <string>
#include <vector>

using namespace std;

std::tuple<int, optional<int>> floor_counter(std::string parens) {

  int current_floor = 0;

  int stairs_taken = 0;
  int basement_visited_after = 0;

  bool basement_visited = false;

  for (char &c : parens) {
    stairs_taken += 1;
    if (c == '(') {
      current_floor += 1;
    } else if (c == ')') {
      current_floor -= 1;
    } else {
      std::cout << "Bad char" << std::endl;
    }

    if (!basement_visited && current_floor < 0) {
      basement_visited = true;
      basement_visited_after = stairs_taken;
    }
  }

  if (basement_visited) {
    return std::make_tuple(current_floor, basement_visited_after);
  } else {
    return std::make_tuple(current_floor, std::nullopt);
  }
}

int main() {
  vector<string> floor_instructions = {
      "(())",
      "()()",
      "(((",
      "(()(()(",
      "))(((((",
      "())",
      "))(",
      ")))",
      ")())())",
      "()())",
      "))())()()((((())))(())()()())()))))((()))"};
  for (string instruction : floor_instructions) {
    cout << endl;
    tuple<int, optional<int>> floor_info = floor_counter(instruction);
    cout << "Checking: " << instruction.substr(0, 20);
    if (instruction.length() > 20) {
      cout << "…";
    }
    cout << endl;

    cout << "Resting floor: " << get<0>(floor_info) << endl;
    if (get<1>(floor_info).has_value()) {
      cout << "Basemenet first visisted at: " << get<1>(floor_info).value()
           << endl;
    }
  }

  // cout << "Puzzle: " << floor_counter(puzzle) << endl;

  return 0;
}
