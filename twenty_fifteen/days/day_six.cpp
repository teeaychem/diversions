#include <fstream>
#include <iostream>
#include <iterator>
#include <ostream>
#include <regex>
#include <string>
#include <vector>

using namespace std;

using binary_grid = vector<vector<bool>>;
using int_grid = vector<vector<int>>;

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

void turn_on(binary_grid *the_grid, int xa, int ya, int xb, int yb) {
  for (int x = xa; x <= xb; x++) {
    for (int y = ya; y <= yb; y++) {
      the_grid->data()[x][y] = true;
    }
  }
}

void turn_off(binary_grid *the_grid, int xa, int ya, int xb, int yb) {
  for (int x = xa; x <= xb; x++) {
    for (int y = ya; y <= yb; y++) {
      the_grid->data()[x][y] = false;
    }
  }
}

void toggle(binary_grid *the_grid, int xa, int ya, int xb, int yb) {
  size_t grid_size = the_grid->size();
  for (int x = xa; x <= xb; x++) {
    for (int y = ya; y <= yb; y++) {
      the_grid->data()[x][y] = !the_grid->data()[x][y];
    }
  }
}

int count_on(binary_grid *the_grid) {
  int count = 0;
  for (size_t x = 0; x < the_grid->size(); x++) {
    for (size_t y = 0; y < the_grid->size(); y++) {
      if (the_grid->data()[x][y]) {
        count += 1;
      };
    }
  }
  return count;
}

binary_grid make_bool_grid(int grid_size) {
  vector<vector<bool>> the_grid{};
  for (int i = 0; i < grid_size; i++) {
    vector<bool> column(grid_size, false);
    the_grid.push_back(column);
  }
  return the_grid;
}

void do_thing(binary_grid *the_grid, string action) {
  regex cmd_regex(
      "(turn on|turn off|toggle) (\\d+),(\\d+) through (\\d+),(\\d+)");
  smatch matches;
  regex_search(action, matches, cmd_regex);

  string cmd = matches[1];
  int xa = stoi(matches[2]);
  int ya = stoi(matches[3]);
  int xb = stoi(matches[4]);
  int yb = stoi(matches[5]);

  if (cmd == "turn on") {
    turn_on(the_grid, xa, ya, xb, yb);
  } else if (cmd == "turn off") {
    turn_off(the_grid, xa, ya, xb, yb);
  } else if (cmd == "toggle") {
    toggle(the_grid, xa, ya, xb, yb);
  } else {
    cout << "Unkown command: " << cmd << endl;
    exit(1);
  }
}

int_grid make_int_grid(int grid_size) {
  int_grid the_grid{};
  for (int i = 0; i < grid_size; i++) {
    vector<int> column(grid_size, 0);
    the_grid.push_back(column);
  }
  return the_grid;
}

void increase(int_grid *the_grid, int xa, int ya, int xb, int yb) {
  for (int x = xa; x <= xb; x++) {
    for (int y = ya; y <= yb; y++) {
      the_grid->data()[x][y] += 1;
    }
  }
}

void decrease(int_grid *the_grid, int xa, int ya, int xb, int yb) {
  for (int x = xa; x <= xb; x++) {
    for (int y = ya; y <= yb; y++) {
      int current_brightness = the_grid->data()[x][y];
      if (current_brightness > 0) {
        the_grid->data()[x][y] = current_brightness - 1;
      }
    }
  }
}

void do_int_thing(int_grid *the_grid, string action) {
  regex cmd_regex(
      "(turn on|turn off|toggle) (\\d+),(\\d+) through (\\d+),(\\d+)");
  smatch matches;
  regex_search(action, matches, cmd_regex);

  string cmd = matches[1];
  int xa = stoi(matches[2]);
  int ya = stoi(matches[3]);
  int xb = stoi(matches[4]);
  int yb = stoi(matches[5]);

  if (cmd == "turn on") {
    increase(the_grid, xa, ya, xb, yb);
  } else if (cmd == "turn off") {
    decrease(the_grid, xa, ya, xb, yb);
  } else if (cmd == "toggle") {
    increase(the_grid, xa, ya, xb, yb);
    increase(the_grid, xa, ya, xb, yb);
  } else {
    cout << "Unkown command: " << cmd << endl;
    exit(1);
  }
}

int count_brightness(int_grid *the_grid) {
  int count = 0;
  for (size_t x = 0; x < the_grid->size(); x++) {
    for (size_t y = 0; y < the_grid->size(); y++) {
      count += the_grid->data()[x][y];
    };
  }
  return count;
}

int main(int argc, char **argv) {

  binary_grid the_grid = make_bool_grid(10);
  cout << count_on(&the_grid) << endl;
  turn_on(&the_grid, 4, 4, 5, 5);
  toggle(&the_grid, 0, 0, 4, 4);
  toggle(&the_grid, 5, 5, 9, 9);
  turn_off(&the_grid, 1, 1, 1, 1);
  turn_off(&the_grid, 9, 9, 9, 9);
  print_grid(the_grid);
  cout << count_on(&the_grid) << endl;

  binary_grid the_grid_two = make_bool_grid(10);
  do_thing(&the_grid_two, "turn on 4,4 through 5,5");
  do_thing(&the_grid_two, "toggle 0,0 through 4,4");
  do_thing(&the_grid_two, "toggle 5,5 through 9,9");
  do_thing(&the_grid_two, "turn off 1,1 through 1,1");
  do_thing(&the_grid_two, "turn off 9,9 through 9,9");
  cout << count_on(&the_grid_two) << endl;
  print_grid(the_grid_two);

  // do_thing(&big_grid, string action)

  if (argc != 2) {
    cout << "A file is needed for anything else…" << endl;
    exit(0);
  }

  string the_file = argv[1];
  ifstream infile(the_file);

  string line;

  binary_grid big_grid = make_bool_grid(1000);
  int_grid big_int_grid = make_int_grid(1000);

  for (string line; getline(infile, line);) {
    do_thing(&big_grid, line);
    do_int_thing(&big_int_grid, line);
  }

  cout << count_on(&big_grid) << endl;
  cout << count_brightness(&big_int_grid) << endl;

  return 0;
}
