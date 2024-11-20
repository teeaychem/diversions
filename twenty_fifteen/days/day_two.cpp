#include <algorithm>
#include <fstream>
#include <iostream>
#include <ostream>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

tuple<int, int> paper_ribbon_needed(vector<int> dimensions) {
  if (dimensions.size() != 3) {
    cout << "hek" << endl;
    exit(1);
  }

  int l = dimensions[0];
  int w = dimensions[1];
  int h = dimensions[2];

  int box = (2 * l * w) + (2 * w * h) + (2 * h * l);

  sort(dimensions.begin(), dimensions.end());
  int extra = dimensions[0] * dimensions[1];

  int paper = box + extra;

  int ribbon_box = 2 * dimensions[0] + 2 * dimensions[1];
  int ribbon_cube = l * w * h;
  int ribbon = ribbon_box + ribbon_cube;

  return make_tuple(paper, ribbon);
}

void print_dimension_info(vector<int> dimensions,
                          tuple<int, int> paper_ribbon) {
  cout << "A box with dimensions " << dimensions[0] << "⨉" << dimensions[1]
       << "⨉" << dimensions[2] << " needs: " << get<0>(paper_ribbon)
       << " sq ft. of paper and " << get<1>(paper_ribbon) << "ft. of ribbon"
       << endl;
}

vector<int> dimensions_from_string(string the_string) {
  size_t position;
  vector<int> dimensions = {};
  while ((position = the_string.find('x')) != string::npos) {
    dimensions.push_back(stoi(the_string.substr(0, position)));
    the_string.erase(0, position + 1);
  }
  dimensions.push_back(stoi(the_string));
  if (dimensions.size() != 3) {
    cout << "hek" << endl;
    exit(1);
  }

  return dimensions;
}

int main(int argc, char **argv) {
  vector<vector<int>> boxes = {{2, 3, 4}, {1, 1, 10}};

  for (auto box : boxes) {
    auto needs = paper_ribbon_needed(box);
    print_dimension_info(box, needs);
  }

  if (argc != 2) {
    cout << "A file is needed for anything else…" << endl;
    exit(0);
  }

  string the_file = argv[1];
  std::ifstream infile(the_file);

  std::string line;
  int total_paper_needed = 0;
  int total_ribbon_needed = 0;

  for (std::string line; getline(infile, line);) {
    vector<int> box = dimensions_from_string(line);
    auto needs = paper_ribbon_needed(box);
    print_dimension_info(box, needs);
    total_paper_needed += get<0>(needs);
    total_ribbon_needed += get<1>(needs);
  }

  cout << "The total paper needed is " << total_paper_needed
       << " sq ft. of paper" << endl;
  cout << "The total ribbon needed is " << total_ribbon_needed
       << " sq ft. of paper" << endl;

  return 0;
}
