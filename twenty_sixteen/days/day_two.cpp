
#include <advent/location.hpp>
#include <fstream>
#include <iostream>
#include <sys/types.h>
#include <unordered_set>
#include <utility>
#include <vector>
using namespace std;

// hek
bool within_diamon_grid(advent::location::coordinate &c) {
  unordered_set<string> options{};
  vector<advent::location::coordinate> diamond{};
  diamond.push_back(pair(2, 0));
  diamond.push_back(pair(1, 1));
  diamond.push_back(pair(2, 1));
  diamond.push_back(pair(3, 1));
  diamond.push_back(pair(0, 2));
  diamond.push_back(pair(1, 2));
  diamond.push_back(pair(2, 2));
  diamond.push_back(pair(3, 2));
  diamond.push_back(pair(4, 2));
  diamond.push_back(pair(1, 3));
  diamond.push_back(pair(2, 3));
  diamond.push_back(pair(3, 3));
  diamond.push_back(pair(2, 4));
  for (auto d : diamond) {
    options.insert(advent::location::location_string(d));
  }

  return options.contains(advent::location::location_string(c));
}

int main(int argc, char **argv) {

  uint keypad_size = 2;
  advent::location::coordinate l = pair(2, 2);

  auto ok_move = [&keypad_size](advent::location::coordinate &tm) {
    return advent::location::within_grid(tm, pair(0, 0),
                                         pair(keypad_size, keypad_size));
    // return within_diamon_grid(tm);
  };

  ifstream infile(argv[1]);
  string all_instructions{};
  for (string line; getline(infile, line);) {
    for (char m : line) {

      advent::location::coordinate n;
      if (m == 'U') {
        n = advent::location::maps_to(l, advent::location::direction::up);
      } else if (m == 'D') {
        n = advent::location::maps_to(l, advent::location::direction::down);
      } else if (m == 'L') {
        n = advent::location::maps_to(l, advent::location::direction::left);
      } else if (m == 'R') {
        n = advent::location::maps_to(l, advent::location::direction::right);
      }

      if (ok_move(n)) {
        l = n;
      }
    }
    cout << advent::location::location_string(l) << endl;
    // cout << ((keypad_size + 1) * (l.second)) + (l.first + 1) << endl;
  }

  return 0;
}
