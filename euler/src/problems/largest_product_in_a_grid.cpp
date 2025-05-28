#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

void largest_product_in_a_grid(int n, ifstream &infile) {

  stringstream ss{};
  string word_buffer{};

  pmr::vector<vector<int>> grid{};

  for (string line; getline(infile, line);) {

    ss << line;
    vector<int> row{};

    while (!ss.eof()) {
      ss >> word_buffer;
      row.push_back(stoi(word_buffer));
    }

    grid.push_back(row);
    ss.clear();
  }

  size_t rows = grid.size();
  size_t cols = grid[0].size();

  int64_t local_product = 1;
  int64_t largest_product = 0;

  for (int r = 0; r < rows; r++) {
    for (int c = 0; c < (cols - n); c++) {

      local_product = 1;

      for (int p = c; p < n; p++) {
        local_product *= grid[r][p];
      }

      if (largest_product < local_product) {
        largest_product = local_product;
      }
    }
  }

  for (int c = 0; c < cols; c++) {
    for (int r = 0; r < (rows - n); r++) {

      local_product = 1;

      for (int p = r; p < n; p++) {
        local_product *= grid[p][c];
      }

      if (largest_product < local_product) {
        largest_product = local_product;
      }
    }
  }

  for (int r = 0; r <= (rows - n); r++) {
    for (int c = 0; c <= (cols - n); c++) {

      local_product = 1;

      for (int p = 0; p < n; p++) {
        local_product *= grid[r + p][c + p];
      }

      if (largest_product < local_product) {
        largest_product = local_product;
      }
    }
  }

  for (int r = n - 1; r < rows; r++) {
    for (int c = 0; c <= (cols - n); c++) {

      local_product = 1;

      for (int p = 0; p < n; p++) {
        local_product *= grid[r - p][c + p];
      }

      if (largest_product < local_product) {
        largest_product = local_product;
      }
    }
  }

  cout << largest_product << endl;
}
