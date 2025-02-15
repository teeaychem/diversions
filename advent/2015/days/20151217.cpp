#include <advent/combinatorics.hpp>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

void print_vector(vector<int> &v) {
  for (auto e : v) {
    cout << e << " ";
  }
  cout << endl;
}

int the_f(vector<int> &containers, int liters) {
  if (liters == 0) {
    return 1;
  } else if (liters < 0 || containers.empty()) {
    return 0;
  } else {
    int last = containers.back();
    containers.pop_back();
    int subways = the_f(containers, liters - last) + the_f(containers, liters);
    containers.push_back(last);

    return subways;
  }
}

int the_g(vector<int> &usage, vector<int> &containers, int liters, int used) {
  if (liters == 0) {
    usage.push_back(used);
    return 1;
  } else if (liters < 0 || containers.empty()) {
    return 0;
  } else {
    int last = containers.back();
    containers.pop_back();
    int subways = the_g(usage, containers, liters - last, used + 1) +
                  the_g(usage, containers, liters, used);
    containers.push_back(last);

    return subways;
  }
}

int main(int argc, char **argv) {

  vector<int> test_containers = {20, 15, 10, 5, 5};
  print_vector(test_containers);
  cout << the_f(test_containers, 25) << endl;

  if (argc != 2) {
    cout << "A file is needed for anything else…" << endl;
    exit(0);
  }

  vector<int> containers{};

  string file = argv[1];
  ifstream infile(file);
  for (string line; getline(infile, line);) {
    containers.push_back(stoi(line));
  }
  print_vector(containers);
  cout << the_f(containers, 150) << endl;

  vector<int> usage{};
  cout << the_g(usage, containers, 150, 0) << endl;

  int the_min = *min_element(usage.begin(), usage.end());
  vector<vector<int>> subvecs = advent::combinatorics::size_k_vectors(containers, the_min);

  int using_the_min{0};
  for (auto v : subvecs) {
    using_the_min += the_f(v, 150);
  }
  cout << using_the_min << endl;

  return 0;
}
