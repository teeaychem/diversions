#include <advent/combinatorics.hpp>
#include <advent/graph.hpp>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <optional>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

int as_int(int x, int y) { return x * 100000 + y; }
int as_int(pair<int, int> p) { return as_int(p.first, p.second); }
int as_int(vector<int> v) {
  if (v.size() != 2) {
    cout << "___" << endl;
    exit(231);
  }
  return as_int(v[0], v[1]);
}

int some_limit = 999;
int zero;

void all_paths(unordered_map<int, vector<pair<int, int>>> &m,
               unordered_set<int> yet_to_vist, int location, int cost_so_far) {
  if (yet_to_vist.empty()) {
    /* part two
    if (location != zero) {
      for (auto x : m[location]) {
        if (x.first == zero) {
          cost_so_far += x.second;
        }
      }
    }
    */


    if (cost_so_far < some_limit) {
      some_limit = cost_so_far;
      cout << "found: " << cost_so_far << endl;
      return;
    }
  }
  if (some_limit < cost_so_far) {
    return;
  }
  for (auto p : m[location]) {
    unordered_set<int> without = yet_to_vist;
    without.erase(p.first);
    all_paths(m, without, p.first, cost_so_far + p.second);
  }
}

int main(int argc, char **argv) {

  vector<string> char_grid{};

  ifstream infile(argv[1]);
  for (string line; getline(infile, line);) {
    char_grid.push_back(line);
  }

  int w = char_grid[0].size();
  int h = char_grid.size();

  vector<vector<int>> points{};

  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      if (char_grid[i][j] != '#' && char_grid[i][j] != '.') {
        if (char_grid[i][j] == '0') {
          zero = as_int(i, j);
          cout << "z: " << zero << endl;
        };
        vector<int> point = vector{i, j};
        points.push_back(point);
      }
    }
  }

  advent::graph::StarGraph<int> g{};

  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      if (char_grid[i][j] != '#') {
        auto around = advent::graph::udlr_points(0, i, h, 0, j, w);
        for (auto p : around) {
          if (char_grid[p.first][p.second] != '#') {
            g.add_edge(advent::graph::WeightedEdge<int>{
                .cost = 1,
                .from = as_int(i, j),
                .to = as_int(p.first, p.second)});
            g.add_edge(advent::graph::WeightedEdge<int>{
                .cost = 1,
                .to = as_int(i, j),
                .from = as_int(p.first, p.second)});
          }
        }
      }
    }
  }

  auto empty_h = [](int) { return 0.0; };

  unordered_map<int, vector<pair<int, int>>> m{};
  unordered_set<int> yet_to_vist{};
  for (auto p : points) {
    yet_to_vist.insert(as_int(p));
    vector<pair<int, int>> x{};
    for (auto px : points) {
      if (px[0] != p[0] || px[1] != p[1]) {
        auto goal_f = [px](auto current) -> bool {
          return current == as_int(px);
        };
        int cost = g.a_star(as_int(p), goal_f, empty_h).value().first;
        // some_limit += cost;
        x.push_back(make_pair(as_int(px), cost));
      }
    }

    m[as_int(p)] = x;
  }

  for (auto mp : m) {
    cout << mp.first << endl;
    for (auto xp : mp.second) {
      cout << "\t" << xp.first << " : " << xp.second << endl;
    }
  }
  // yet_to_vist.erase(zero);

  all_paths(m, yet_to_vist, zero, 0);

  return 0;
}
