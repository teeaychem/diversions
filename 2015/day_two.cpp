#include <fstream>
#include <iostream>
#include <optional>
#include <ostream>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

int paper_needed(vector<int> dimensions) {
  if (dimensions.size() != 3) {
    cout << "hek" << endl;
    exit(1);
  }

  int l = dimensions[0];
  int w = dimensions[1];
  int h = dimensions[2];

  int box = (2 * l * w) + (2 * w * h) + (2 * h * l);

  int extra;
  if (l >= w && l >= h) {
    extra = w * h;
  } else if (w >= l && w >= h) {
    extra = l * h;
  } else {
    extra = w * l;
  }

  return box + extra;
}

void print_dimension_info(vector<int> dimensions, int needs) {
  cout << "A box with dimensions " << dimensions[0] << "⨉" << dimensions[1]
       << "⨉" << dimensions[2] << " needs: " << needs << " sq ft. of paper"
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

int main() {
  vector<vector<int>> boxes = {{2, 3, 4}, {1, 1, 10}};

  for (auto box : boxes) {
    int needs = paper_needed(box);
    print_dimension_info(box, needs);
  }

  std::ifstream infile("day_two_dimensions.txt");
  std::string line;
  int total_required = 0;

  for (std::string line; getline(infile, line);) {
    vector<int> box = dimensions_from_string(line);
    int needs = paper_needed(box);
    print_dimension_info(box, needs);
    total_required += needs;
  }

  cout << "The total paper required is " << total_required << " sq ft. of paper"
       << endl;

  return 0;
}
