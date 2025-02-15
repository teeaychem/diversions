
#include <advent/combinatorics.hpp>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <vector>

using namespace std;

void swap_position(string &s, int i, int j) { swap(s[i], s[j]); }

void swap_character(string &s, char a, char b) {
  swap(s[s.find(a)], s[s.find(b)]);
}

void rotate_left(string &s, int steps) {
  int x = steps % s.size();
  string left = s.substr(0, x);
  string right = s.substr(x, s.size());
  s = right + left;
}

void rotate_right(string &s, int steps) {
  int x = s.size() - (steps % s.size());
  string left = s.substr(0, x);
  string right = s.substr(x, s.size());
  s = right + left;
}

void rotate_char(string &s, char c) {
  int p = s.find(c);
  if (p >= 4) {
    p++;
  }
  rotate_right(s, p + 1);
}

void reverse_through(string &s, int i, int j) {
  reverse(s.begin() + i, s.begin() + j + 1);
}

void move(string &s, int i, int j) {
  if (i < j) {
    for (; i < j; i++) {
      swap_position(s, i, i + 1);
    }
  } else if (j < i) {
    for (; j < i; i--) {
      swap_position(s, i, i - 1);
    }
  }
}

void test() {
  string s = "abcde";
  swap_position(s, 4, 0);
  cout << s << endl;
  swap_character(s, 'b', 'd');
  cout << s << endl;
  reverse_through(s, 0, 4);
  cout << s << endl;
  rotate_left(s, 1);
  cout << s << endl;
  move(s, 1, 4);
  cout << s << endl;
  move(s, 3, 0);
  cout << s << endl;
  rotate_char(s, 'b');
  cout << s << endl;
  rotate_char(s, 'd');
  cout << s << endl;
}

void do_thing(string &s, string action) {
  regex a("swap position (\\d+) with position (\\d+)");
  regex b("swap letter ([a-z]) with letter ([a-z])");
  regex c("rotate left (\\d+) step(s?)");
  regex d("rotate right (\\d+) step(s?)");
  regex e("rotate based on position of letter ([a-z])");
  regex f("reverse positions (\\d+) through (\\d+)");
  regex g("move position (\\d+) to position (\\d+)");

  smatch matches;
  if (regex_search(action, matches, a)) {
    swap_position(s, stoi(matches[1]), stoi(matches[2]));
  } else if (regex_search(action, matches, b)) {
    swap_character(s, matches[1].str()[0], matches[2].str()[0]);
  } else if (regex_search(action, matches, c)) {
    rotate_left(s, stoi(matches[1]));
  } else if (regex_search(action, matches, d)) {
    rotate_right(s, stoi(matches[1]));
  } else if (regex_search(action, matches, e)) {
    rotate_char(s, matches[1].str()[0]);
  } else if (regex_search(action, matches, f)) {
    reverse_through(s, stoi(matches[1]), stoi(matches[2]));
  } else if (regex_search(action, matches, g)) {
    move(s, stoi(matches[1]), stoi(matches[2]));
  } else {
    cout << ">>> " << action << endl;
    exit(213421312);
  }
}

void permute_helper(vector<string> &ps, string &s, size_t l, size_t r) {
  if (l == r) {
    ps.push_back(s);
  } else {
    for (size_t i = l; i <= r; i++) {
      swap(s[l], s[i]);
      permute_helper(ps, s, l + 1, r);
      swap(s[l], s[i]);
    }
  }
}

vector<string> permute(string s) {
  vector<string> ps{};
  permute_helper(ps, s, 0, s.size());
  return ps;
}

int main(int argc, char **argv) {

  string s = "abcdefgh";

  string the_file = argv[1];
  ifstream infile(the_file);

  string line;
  vector<string> acts{};

  for (string line; getline(infile, line);) {
    acts.push_back(line);
  }
  for (auto act : acts) {
    do_thing(s, act);
    cout << s << endl;
  }

  string two = "abcdefgh";
  auto lol = permute(two);
  for (auto no : lol) {
    cout << no << endl;
    for (auto act : acts) {
      do_thing(no, act);
    }
    if (no == "fbgdceah") {
      exit(21312312);
    }
  }

  exit(0);
}
