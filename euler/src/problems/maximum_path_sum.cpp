#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

void maximum_path_sum(ifstream &triangle_file) {

  vector<vector<int>> triangle = {};

  string line;

  if (triangle_file.is_open()) {
    while (getline(triangle_file, line)) {
      vector<int> part{};
      int value{};
      stringstream values{line};
      while (values >> value) {
        part.push_back(value);
      }
      triangle.push_back(part);
    }
    triangle_file.close();
  } else {
    cout << "Unable to open file" << "\n";
  }

  printf("The triangle has height %zu\n", triangle.size());

  // Work backwards taking the optimal move each step.
  for (int i = triangle.size() - 2; 0 <= i; --i) {
    for (int j = 0; j < triangle[i].size(); ++j) {
      triangle[i][j] += max(triangle[i + 1][j], triangle[i + 1][j + 1]);
    }
  }

  printf("The maximum path through the triangle totals: %d\n", triangle[0][0]);
}
