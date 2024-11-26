#include <advent/combinatorics.hpp>
#include <advent/strings.hpp>
#include <climits>
#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <limits>
#include <ostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

int main(int argc, char **argv) {
  unordered_set<int> test_ints = {0, 1, 2, 3};
  auto int_result = advent::combinatorics::permute(test_ints);
  advent::combinatorics::display_permutations(&int_result);

  unordered_set<string> test_strings = {"a", "be", "sea"};
  auto string_result = advent::combinatorics::permute(test_strings);
  advent::combinatorics::display_permutations(&string_result);

  unordered_map<string, unordered_map<string, size_t>>
      location_location_distance;

  if (argc != 2) {
    cout << "A file is needed for anything more…" << endl;
    exit(0);
  }

  string the_file = argv[1];
  ifstream infile(the_file);

  for (string line; getline(infile, line);) {
    auto y = advent::string::string_split_delim(line, " ");
    location_location_distance[y[0]][y[2]] = stoi(y[4]);
  }

  unordered_set<string> locations{};
  for (auto map_a : location_location_distance) {
    locations.insert(map_a.first);
    for (auto map_b : map_a.second) {
      locations.insert(map_b.first);
    }
  }

  auto location_permutations = advent::combinatorics::permute(locations);

  unsigned int min_distance = numeric_limits<unsigned int>::max();
  unsigned int max_distance = numeric_limits<unsigned int>::min();

  for (size_t p = 0; p < location_permutations.size(); p++) {
    auto permutation = location_permutations[p];
    unsigned int distance = 0;
    for (size_t i = 1; i < permutation.size(); i++) {
      string location_a = permutation[i - 1];
      string location_b = permutation[i];

      if (location_location_distance.contains(location_a) &&
          location_location_distance[location_a].contains(location_b)) {
        distance += location_location_distance[location_a][location_b];
      } else if (location_location_distance.contains(location_b) &&
                 location_location_distance[location_b].contains(location_a)) {
        distance += location_location_distance[location_b][location_a];
      } else {
        cout << "x_x" << endl;
        exit(1);
      }

      cout << location_a << " -> " << location_b << " ";
    }
    cout << " = " << distance << endl;
    if (distance < min_distance) {
      min_distance = distance;
    }
    if (distance > max_distance) {
      max_distance = distance;
    }
  }
  cout << "min: " << min_distance << endl;
  cout << "max: " << max_distance << endl;
}
