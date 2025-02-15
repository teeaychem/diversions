#include <algorithm>
#include <climits>
#include <cmath>
#include <functional>
#include <iostream>
#include <iterator>
#include <limits>
#include <optional>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

typedef unsigned long tt;

void check(vector<vector<int>> positions, int limit) {
  tt time = 1;
  for (; time <= limit; time++) {
    for (size_t d = 0; d < positions.size(); d++) {
      positions[d][1] = ((positions[d][1] + 1) % positions[d][0]);
    }
  }
  cout << "time " << time << endl;
  for (size_t i = 0; i < positions.size(); i++) {
    cout << "\t" << i << " : " << positions[i][1] << "(" << positions[i][0]
         << ")" << endl;
  }
}

optional<int> part_one(vector<vector<int>> positions) {
  unordered_map<int, int> m{};

  tt tt_max = numeric_limits<tt>::max();
  tt limit = tt_max;
  for (tt time = 1; time < limit; time++) {
    for (size_t d = 0; d < positions.size(); d++) {
      positions[d][1] = ((positions[d][1] + 1) % positions[d][0]);
    }
    // cout << "time " << time << endl;
    // for (size_t i = 0; i < positions.size(); i++) {
    //   cout << "\t" << i << " : " << positions[i][1] << endl;
    // }

    erase_if(m, [&positions](const auto &item) {
      auto const &[k, v] = item;
      // cout << "checking t : " << k << " on " << v << "  "
      //      << ((positions[v][1] % positions[v][0]) != 0) << endl;
      return positions[v][1] % positions[v][0] != 0;
    });

    for (auto &p : m) {
      cout << "\tconsidering:" << endl;
      cout << "\t\t" << p.first << " " << p.second << endl;
      if (p.second == positions.size() - 1 &&
          positions[p.second][1] % positions[p.second][0] == 0) {
        cout << "drop " << p.first - 1 << endl;
        return p.first - 1;
      } else {
        p.second += 1;
      }
    }

    if (positions[0][1] % positions[0][0] == 0) {
      m[time] = 1;
    }
  }
  return nullopt;
}

int main(int argc, char **argv) {

  vector<vector<int>> test_positions{};
  test_positions.push_back({5, 4});
  test_positions.push_back({2, 1});
  part_one(test_positions);
  check(test_positions, 5);

  // vector<vector<int>> positions{};
  // auto drop_at = part_one(positions);
  // if (drop_at.has_value()) {
  //   check(positions, drop_at.value());
  // }

  return 0;
}
