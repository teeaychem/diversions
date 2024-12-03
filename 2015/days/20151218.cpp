#include <algorithm>
#include <cstddef>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <vector>

using namespace std;
typedef vector<vector<int>> grid;

void print_grid(grid the_grid) {
  for (auto r : the_grid) {
    for (auto c : r) {
      if (c == 0) {
        cout << '.';
      } else if (c == 1) {
        cout << '#';
      }
      // cout << " ";
    }
    cout << endl;
  }
};

void print_index(int x, int y) { cout << x << " " << y << endl; }

int count_on(grid &the_grid) {
  int the_count{0};
  for (size_t i = 0; i < the_grid.size(); i++) {
    for (size_t j = 0; j < the_grid.size(); j++) {
      if (the_grid[j][i] == 1) {
        the_count += 1;
      }
    }
  }
  return the_count;
}

void grid_neighbours(int x, int y, int n, function<void(int, int)> f) {
  for (int i = max(0, x - 1); i <= min(n - 1, x + 1); i++) {
    for (int j = max(0, y - 1); j <= min(n - 1, y + 1); j++) {
      if (i != x || j != y) {
        f(i, j);
      }
    }
  }
}

grid diagram_to_grid(string diagram) {
  grid the_grid{};
  vector<int> line{};
  for (char c : diagram) {
    if (c == '.') {
      line.push_back(0);
    } else if (c == '#') {
      line.push_back(1);
    } else if (c == '\n') {
      vector<int> finished_line{};
      copy(line.begin(), line.end(), back_insert_iterator(finished_line));
      line.clear();
      the_grid.push_back(finished_line);
    }
  }
  the_grid.push_back(line);

  return the_grid;
}

int neighbour_on_count(grid &the_grid, int x, int y) {
  int count{0};
  auto counter = [&count, &the_grid](int x, int y) {
    if (the_grid[y][x] == 1) {
      count += 1;
    }
  };

  grid_neighbours(x, y, the_grid.size(), counter);
  return count;
}

void update_grid(grid &the_grid) {
  grid prior_test_grid = the_grid;

  for (size_t i = 0; i < the_grid.size(); i++) {
    for (size_t j = 0; j < the_grid.size(); j++) {
      int on_neighbours = neighbour_on_count(prior_test_grid, i, j);
      if (prior_test_grid[j][i] == 1) {
        if (on_neighbours == 2 || on_neighbours == 3) {
          the_grid[j][i] = 1;
        } else {
          the_grid[j][i] = 0;
        }
      }

      if (prior_test_grid[j][i] == 0) {
        if (on_neighbours == 3) {
          the_grid[j][i] = 1;
        } else {
          the_grid[j][i] = 0;
        }
      }
    }
  }
}

int main(int argc, char **argv) {

    string test_diagram = R"(.#.#.#
  ...##.
  #....#
  ..#...
  #.#..#
  ####..)";

    grid test_grid = diagram_to_grid(test_diagram);
    print_grid(test_grid);

    for (int i = 0; i < 4; i++) {
      update_grid(test_grid);
    }

    cout << endl;

    print_grid(test_grid);

    cout << count_on(test_grid) << endl;

  exit(1);

  string the_diagram = R"()";

  grid the_grid = diagram_to_grid(the_diagram);
  print_grid(the_grid);

  int n = 100;
  for (int i = 0; i < n; i++) {
    update_grid(the_grid);
    the_grid[0][0] = 1;
    the_grid[0][n - 1] = 1;
    the_grid[n - 1][0] = 1;
    the_grid[n - 1][n - 1] = 1;
  }

  cout << endl;

  print_grid(the_grid);

  cout << count_on(the_grid) << endl;

  return 0;
}
