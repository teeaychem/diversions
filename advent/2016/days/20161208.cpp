#include <fstream>
#include <iostream>
#include <ostream>
#include <regex>
#include <string>
#include <vector>

using namespace std;

using binary_grid = vector<vector<bool>>;

void print_grid(binary_grid the_grid) {
  for (auto column : the_grid) {
    cout << "|";
    for (auto v : column) {
      if (v) {
        cout << "+";
      } else {
        cout << " ";
      }
    }
    cout << "|" << endl;
  }
}

int count_on(binary_grid &the_grid) {
  int count = 0;
  for (size_t x = 0; x < the_grid.size(); x++) {
    for (size_t y = 0; y < the_grid[x].size(); y++) {
      if (the_grid.data()[x][y]) {
        count += 1;
      };
    }
  }
  return count;
}

binary_grid make_bool_grid(int r, int c) {
  vector<vector<bool>> the_grid = vector(r, vector(c, false));
  return the_grid;
}

void grid_on(binary_grid &g, int r, int c) {
  for (int i = 0; i < r; i++) {
      for (int j = 0; j < c; j++) {
        g[i][j] = true;
      }
    }
}

void shift_right(binary_grid &g, int r) {
  size_t row_size = g[r].size();
  for (size_t j = row_size; 1 < j; j--) {
    swap(g[r][j - 1], g[r][j - 2]);
  }
}

void shift_down(binary_grid &g, int c) {
  size_t column_size = g.size();
  for (size_t j = column_size; 1 < j; j--) {
    swap(g[j - 1][c], g[j - 2][c]);
  }
}

void do_thing(binary_grid &the_grid, string action) {
  regex on_regex("rect (\\d+)x(\\d+)");
  regex row_regex("rotate row y=(\\d+) by (\\d+)");
  regex col_regex("rotate column x=(\\d+) by (\\d+)");
  smatch matches;
  if (regex_search(action, matches, on_regex)) {
    int r = stoi(matches[2]);
    int c = stoi(matches[1]);
    cout << "rect " << r << "x" << c << endl;
    grid_on(the_grid, r, c);

  } else if (regex_search(action, matches, row_regex)) {
    int r = stoi(matches[1]);
    int by = stoi(matches[2]);
    cout << "rotate row" << r << ":" << by << endl;
    for (int i = 0; i < by; i++) {
      shift_right(the_grid, r);
    }
  } else if (regex_search(action, matches, col_regex)) {
    int c = stoi(matches[1]);
    int by = stoi(matches[2]);
    cout << "rotate column" << c << ":" << by << endl;
    for (int i = 0; i < by; i++) {
      shift_down(the_grid, c);
    }
  } else {
    cout << "no things found: " << action << endl;
  }
}

int main(int argc, char **argv) {

  if (argc != 2) {
    cout << "A file is needed for anything else…" << endl;
    exit(0);
  }

  string the_file = argv[1];
  ifstream infile(the_file);

  string line;

  binary_grid big_grid = make_bool_grid(6, 50);


  for (string line; getline(infile, line);) {
    do_thing(big_grid, line);
    print_grid(big_grid);
  }
  cout << "on: " << count_on(big_grid) << endl;;

  return 0;
}
