
#include "./../../lib/combinatorics.hpp"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <limits>
#include <regex>
#include <string>
#include <unordered_map>
#include <unordered_set>

using namespace std;

int main(int argc, char **argv) {

  if (argc != 2) {
    cout << "A file is needed for anything else…" << endl;
    exit(0);
  }

  bool seat_mylself = true;

  unordered_map<string, unordered_map<string, int>> happiness_map{};
  unordered_set<string> names{};

  string the_file = argv[1];
  ifstream infile(the_file);

  string line;
  regex cmd_regex("([A-Z][a-z]+) would (gain|lose) (\\d+) happiness units by "
                  "sitting next to ([A-Z][a-z]+)");
  smatch matches;

  for (string line; getline(infile, line);) {
    if (regex_search(line, matches, cmd_regex)) {
      string subject = matches[1];
      string object = matches[4];
      bool gain = matches[2] == "gain";
      unsigned int amount = stoi(matches[3]);

      happiness_map[subject][object] = gain ? amount : -amount;
      names.insert(subject);
    } else {
      cout << "x_x" << endl;
      exit(1);
    }
  }

  if (seat_mylself) {

    string my_name = "Joker";
    for (string name : names) {
      happiness_map[name][my_name] = 0;
      happiness_map[my_name][name] = 0;
    }
    names.insert(my_name);
  }

  vector<vector<string>> arrangements = combinatorics::permute(names);
  combinatorics::display_permutations(&arrangements);

  vector<string> optimal_seating;
  int max_happiness = numeric_limits<int>::min();
  int variance = 0;

  for (auto seating : arrangements) {
    int score = 0;
    int difference = 0;
    for (size_t i = 1; i < seating.size(); i++) {
      int left = happiness_map[seating[i]][seating[i - 1]];
      int right = happiness_map[seating[i - 1]][seating[i]];

      score += (left + right);
      difference += abs(left - right);
    }
    int left = happiness_map[seating[seating.size() - 1]][seating[0]];
    int right = happiness_map[seating[0]][seating[seating.size() - 1]];

    score += (left + right);
    difference += abs(left - right);

    if (score > max_happiness) {
      optimal_seating = seating;
      max_happiness = score;
      variance = difference;
    }
  }
  cout << max_happiness << endl;
  cout << variance << endl;
  for (auto seat : optimal_seating) {
    cout << seat << " ";
  }
  cout << endl;

  return 0;
}
