#include <climits>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <fstream>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>

using namespace std;

template <typename element>
vector<vector<element>> permute(unordered_set<element> elements) {
  if (elements.empty()) {
    return vector<vector<element>>{vector<element>{}};
  }

  vector<vector<element>> out_vec;
  for (element e : elements) {
    unordered_set<element> elements_without{};
    for (auto other_e : elements) {
      if (e != other_e) {
        elements_without.insert(other_e);
      }
    }

    vector<vector<element>> subpermutations = permute(elements_without);
    for (auto sp : subpermutations) {
      sp.push_back(e);
      out_vec.push_back(sp);
    }
  }
  return out_vec;
}

vector<string> string_split_delim(string input, string delimiter) {
  vector<string> split;

  size_t pos = 0;
  while ((pos = input.find(delimiter)) != string::npos) {
    split.push_back(input.substr(0, pos));
    input.erase(0, pos + delimiter.length());
  }
  split.push_back(input);

  return split;
}

template <typename element>
void display_permutations(vector<vector<element>> *permutations) {
  for (size_t p = 0; p < permutations->size(); p++) {
    vector<element> permutation = permutations->data()[p];
    cout << "(  ";
    for (size_t i = 1; i < permutation.size(); i++) {
      cout << permutation[i - 1] << " -> " << permutation[i] << "  ";
    }
    cout << ")" << endl;
  }
}

int main(int argc, char **argv) {
  unordered_set<int> test_ints = {0, 1, 2, 3};
  auto int_result = permute(test_ints);
  display_permutations(&int_result);

  unordered_set<string> test_strings = {"a", "be", "sea"};
  auto string_result = permute(test_strings);
  display_permutations(&string_result);

  unordered_map<string, unordered_map<string, size_t>>
      location_location_distance;


  if (argc != 2) {
    cout << "A file is needed for anything more…" << endl;
    exit(0);
  }

  string the_file = argv[1];
  ifstream infile(the_file);

  for (string line; getline(infile, line);) {
    auto y = string_split_delim(line, " ");
    location_location_distance[y[0]][y[2]] = stoi(y[4]);
  }

  unordered_set<string> locations{};
  for (auto map_a : location_location_distance) {
    locations.insert(map_a.first);
    for (auto map_b : map_a.second) {
      locations.insert(map_b.first);
    }
  }

  auto location_permutations = permute(locations);

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
