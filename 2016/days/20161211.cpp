
#include <advent/combinatorics.hpp>
#include <algorithm>
#include <functional>
#include <iostream>
#include <limits>
#include <queue>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;
typedef unsigned long long int_rep;

int shortest = numeric_limits<int>::max();

template <typename element>
string join(const element &v, const string &delimiter) {
  string s{};
  for (auto &e : v) {
    if (e != v[0]) {
      s += delimiter;
    }
    s += e;
  }
  return s;
}

void print_map(vector<int> const &l) {
  for (size_t i = 0; i < l.size(); i++) {
    cout << l[i] << " ";
  }
  cout << endl;
}

vector<int_rep> as_ints(vector<int> const &l, int f) {
  vector<int_rep> the_ints{};
  for (size_t pair_idx = 0; pair_idx < l.size(); pair_idx += 2) {
    int_rep the_i = f;
    for (size_t i = 0; i < l.size(); i++) {
      size_t ix = (i + pair_idx) % l.size();
      the_i += l[ix] * pow(10, i + 1);
    }
    the_ints.push_back(the_i);
  }
  return the_ints;
}

vector<int_rep> as_ints_moves(vector<int> const &l, int f, int m) {
  vector<int_rep> the_ints{};
  for (size_t pair_idx = 0; pair_idx < l.size(); pair_idx += 2) {
    int_rep the_i = f;
    the_i += m * 10;
    for (size_t i = 0; i < l.size(); i++) {
      size_t ix = (i + pair_idx) % l.size();
      the_i += l[ix] * pow(10, i + 2);
    }
    the_ints.push_back(the_i);
  }
  return the_ints;
}

bool blow_up(vector<int> const &l, int f) {
  for (size_t m_idx = 1; m_idx < l.size(); m_idx = m_idx + 2) {
    if (l[m_idx - 1] != l[m_idx]) { // not paired with generator
      for (int g_idx = 0; g_idx < l.size(); g_idx = g_idx + 2) {
        if (l[g_idx] == l[m_idx]) { // && l[g_idx] != l[g_idx + 1]
          // cout << "blow up: " << as_int(l, f) << " (" << m_idx << "," <<
          // g_idx
          //      << ")"
          //      << "&&" << l[m_idx - 1] << "!=" << l[m_idx] << endl;
          // print_map(l);
          return true;
        }
      }
    }
  }
  return false;
}

bool finished(vector<int> &l, int t) {
  for (size_t i = 0; i < l.size(); i++) {
    if (l[i] != t) {
      return false;
    }
  }
  return true;
}

vector<int> things_on_floor(vector<int> const &l, int f) {
  vector<int> things{};
  for (size_t i = 0; i < l.size(); i++) {
    if (l[i] == f) {
      things.push_back(i);
    }
  }
  return things;
}

unordered_map<int_rep, int> seen{};

void exhaust_it(vector<int> &l, int b, int f, int t, int m) {
  if (shortest < m) { // only continue if new optimum is possible
    return;
  }

  // cout << "searching (" << f << " : " << as_an_int << ")" << endl;

  if (finished(l, t)) {
    if (m < shortest) { // done?
      cout << "found shortest: " << m << endl;
      shortest = m;
    }
    return;
  }

  m += 1;

  vector<int_rep> int_reps = as_ints(l, f);
  int_rep c_rep = int_reps[0];
  try { // already been here
    if (seen.at(c_rep) < m) {
      return;
    } else if (seen.at(c_rep) > m) {
      for (auto rep : int_reps) {
        seen[rep] = m;
      }
    }
  } catch (out_of_range) {
    for (auto rep : int_reps) {
      seen[rep] = m;
    }
  }

  if (blow_up(l, f)) { // problem?
    return;
  }

  const vector<int> on_floor = things_on_floor(l, f);
  const vector<vector<int>> pairs_on_floor =
      advent::combinatorics::size_k_vectors(on_floor, 2);

  vector<vector<int>> unified{};
  for (size_t p_idx = 0; p_idx < pairs_on_floor.size(); p_idx++) {
    vector<int> copy = pairs_on_floor[p_idx];
    unified.push_back(copy);
  }
  for (size_t f_idx = 0; f_idx < on_floor.size(); f_idx++) {
    vector<int> unit = vector(1, on_floor[f_idx]);
    unified.push_back(unit);
  }

  b = *min_element(l.begin(), l.end());

  for (size_t u = 0; u < unified.size(); u++) {
    if (f < t) {
      for (size_t x = 0; x < unified[u].size(); x++) {
        l[unified[u][x]] += 1;
      }
      exhaust_it(l, b, f + 1, t, m);
      for (size_t x = 0; x < unified[u].size(); x++) {
        l[unified[u][x]] -= 1;
      }
      if (seen.at(c_rep) < m || shortest < m) {
        return;
      }
    }

    if (b < f) { // && unified[u].size() == 1) {
      for (size_t x = 0; x < unified[u].size(); x++) {
        l[unified[u][x]] -= 1;
      }
      exhaust_it(l, b, f - 1, t, m);
      for (size_t x = 0; x < unified[u].size(); x++) {
        l[unified[u][x]] += 1;
      }
      if (seen.at(c_rep) < m || shortest < m) {
        return;
      }
    }
  }

  return;
}

struct pair_thing {
  string n;
  int g;
  int m;

  bool operator==(const pair_thing &o) const {
    return n == o.n && g == o.g && m == o.m;
  }

  string to_string() const {
    return "'" + n + "'" + ::to_string(g) + ::to_string(m);
  }

  size_t hash() const { return std::hash<string>()(to_string()); }

  size_t sum_hash() const { return std::hash<int>()(g + m); }
};

struct pair_thing_hash {
  size_t operator()(const pair_thing &pt) const { return (pt.hash()); }
};

struct pair_thing_sum_hash {
  size_t operator()(const pair_thing &pt) const { return (pt.sum_hash()); }
};

struct bfs_struct {
  unordered_set<pair_thing, pair_thing_hash> things;
  int f;
  int m;

  string to_string() const {
    string s{};
    s += ::to_string(f);
    s += " ";
    s += things_sum();
    return s;
  }

  string things_sum() const {
    string s {};
    vector<int> sums{};
    for (auto t : things) {
      sums.push_back(t.g + t.m * 10);
    }
    sort(sums.begin(), sums.end(), less<int>());
    for (auto sum : sums) {
      s += ::to_string(sum);
    }
    return s;
  }

  bool operator==(const bfs_struct &o) const {
    return things_sum() == o.things_sum() && f == o.f && m == o.m;
  }

  size_t hash() const { return std::hash<string>()(to_string()); }
};

struct bfs_struct_hash {
  size_t operator()(const bfs_struct &s) const { return (s.hash()); }
};

bool finished(bfs_struct &bfsm, int top) {
  for (auto t : bfsm.things) {
    if (t.g != top || t.m != top) {
      return false;
    }
  }
  return true;
}

bool blow_up(bfs_struct &bfsm) {
  for (auto t : bfsm.things) {
    if (t.g != t.m) {
      for (auto to : bfsm.things) {
        if (t.n != to.n && t.m == to.g) {
          return true;
        }
      }
    }
  }
  return false;
}

vector<pair<string, char>> things_on_floor(bfs_struct &s) {
  vector<pair<string, char>> v{};
  for (auto t : s.things) {
    if (t.g == s.f) {
      pair<string, char> x = {t.n, 'g'};
      v.push_back(x);
    }
    if (t.m == s.f) {
      pair<string, char> x = {t.n, 'm'};
      v.push_back(x);
    }
  }
  return v;
}

int lowest(bfs_struct &s) {
  int l = numeric_limits<int>::max();
  for (auto t : s.things) {
    if (t.g < l) {
      l = t.g;
    }
    if (t.m < l) {
      l = t.m;
    }
  }
  return l;
}

void exhaust_it_bfs(bfs_struct start, int top) {

  // cout << "searching (" << f << " : " << as_an_int << ")" << endl;
  unordered_set<string> seen{};
  queue<bfs_struct> q{};
  q.push(start);

  while (!q.empty()) {
    auto front = q.front();
    q.pop();
    if (!seen.contains(front.to_string())) {
      int offset = 3;
      seen.insert(front.to_string());
      string hash_a = front.to_string();
      hash_a[offset] = 'a';
      hash_a[offset + 6] = 'b';
      hash_a[offset + 6 * 2] = 'c';
      hash_a[offset + 6 * 3] = 'd';
      hash_a[offset + 6 * 4] = 'e';
      hash_a[offset + 6 * 5] = 'f';
      hash_a[offset + 6 * 6] = 'g';
      seen.insert(hash_a);

      string hash_b = front.to_string();
      hash_b[offset] = 'b';
      hash_b[offset + 6] = 'c';
      hash_b[offset + 6 * 2] = 'd';
      hash_b[offset + 6 * 3] = 'e';
      hash_b[offset + 6 * 4] = 'f';
      hash_b[offset + 6 * 5] = 'g';
      hash_b[offset + 6 * 6] = 'a';
      seen.insert(hash_b);

      string hash_c = front.to_string();
      hash_c[offset] = 'c';
      hash_c[offset + 6] = 'd';
      hash_c[offset + 6 * 2] = 'e';
      hash_c[offset + 6 * 3] = 'f';
      hash_c[offset + 6 * 4] = 'g';
      hash_c[offset + 6 * 5] = 'a';
      hash_c[offset + 6 * 6] = 'b';
      seen.insert(hash_c);

      string hash_d = front.to_string();
      hash_d[offset] = 'd';
      hash_d[offset + 6] = 'e';
      hash_d[offset + 6 * 2] = 'f';
      hash_d[offset + 6 * 3] = 'g';
      hash_d[offset + 6 * 4] = 'a';
      hash_c[offset + 6 * 5] = 'b';
      hash_c[offset + 6 * 6] = 'c';
      seen.insert(hash_d);

      string hash_e = front.to_string();
      hash_e[offset] = 'e';
      hash_e[offset + 6] = 'f';
      hash_e[offset + 6 * 2] = 'g';
      hash_e[offset + 6 * 3] = 'a';
      hash_e[offset + 6 * 4] = 'b';
      hash_e[offset + 6 * 5] = 'c';
      hash_e[offset + 6 * 6] = 'd';
      seen.insert(hash_e);

      string hash_f = front.to_string();
      hash_f[offset] = 'f';
      hash_f[offset + 6] = 'g';
      hash_f[offset + 6 * 2] = 'a';
      hash_f[offset + 6 * 3] = 'b';
      hash_f[offset + 6 * 4] = 'c';
      hash_f[offset + 6 * 5] = 'd';
      hash_f[offset + 6 * 6] = 'e';
      seen.insert(hash_f);

      string hash_g = front.to_string();
      hash_g[offset] = 'g';
      hash_g[offset + 6] = 'a';
      hash_g[offset + 6 * 2] = 'b';
      hash_g[offset + 6 * 3] = 'c';
      hash_g[offset + 6 * 4] = 'd';
      hash_g[offset + 6 * 5] = 'e';
      hash_g[offset + 6 * 6] = 'f';
      seen.insert(hash_g);

      if (finished(front, top)) {
        if (front.m < shortest) {
          shortest = front.m;
          cout << "shortest: " << shortest << endl;
        }

      } else if (blow_up(front)) {
        // cout << "bu" << endl;
      } else if (front.m < shortest) {
        cout << "popped: " << front.to_string() << " moves: " << front.m
             << endl;

        auto on_floor = things_on_floor(front);
        auto pairs_on_floor =
            advent::combinatorics::size_k_vectors(on_floor, 2);
        // for (auto x : on_floor) {
        //   cout << x.first << " " << x.second << endl;
        // }
        // for (auto x : pairs_on_floor) {
        //   for (auto y : x) {
        //     cout << y.first << " " << y.second << " - ";
        //   }
        //   cout << endl;
        // }

        if (front.f < top) {
          for (auto tof : on_floor) {
            bfs_struct n{};
            n.f = front.f + 1;
            n.m = front.m + 1;
            for (auto t : front.things) {
              pair_thing tc = t;
              if (t.n == tof.first) {
                if (tof.second == 'g') {
                  tc.g += 1;
                } else if (tof.second == 'm') {
                  tc.m += 1;
                }
              }
              n.things.insert(tc);
            }
            q.push(n);
          }

          for (auto pof : pairs_on_floor) {
            bfs_struct n{};
            n.f = front.f + 1;
            n.m = front.m + 1;
            for (auto t : front.things) {
              pair_thing tc = t;
              for (size_t i = 0; i < pof.size(); i++) {
                if (t.n == pof[i].first) {
                  if (pof[i].second == 'g') {
                    tc.g += 1;
                  } else if (pof[i].second == 'm') {
                    tc.m += 1;
                  }
                }
              }
              n.things.insert(tc);
            }
            // cout << n.to_string() << endl;
            q.push(n);
          }
        }

        if (lowest(front) < front.f) {
          for (auto tof : on_floor) {
            bfs_struct n{};
            n.f = front.f - 1;
            n.m = front.m + 1;
            for (auto t : front.things) {
              pair_thing tc = t;
              if (t.n == tof.first) {
                if (tof.second == 'g') {
                  tc.g -= 1;
                } else if (tof.second == 'm') {
                  tc.m -= 1;
                }
              }
              n.things.insert(tc);
            }
            q.push(n);
          }

          for (auto pof : pairs_on_floor) {
            bfs_struct n{};
            n.f = front.f - 1;
            n.m = front.m + 1;
            for (auto t : front.things) {
              pair_thing tc = t;
              for (size_t i = 0; i < pof.size(); i++) {
                if (t.n == pof[i].first) {
                  if (pof[i].second == 'g') {
                    tc.g -= 1;
                  } else if (pof[i].second == 'm') {
                    tc.m -= 1;
                  }
                }
              }
              n.things.insert(tc);
            }
            // cout << n.to_string() << endl;
            q.push(n);
          }
        }
      }
    }
  }
}

int main(int argc, char **argv) {

  // vector<int> locations = {2, 1, 3, 1};
  // pair_thing test_a{
  //     .n = "h",
  //     .g = 2,
  //     .m = 1,
  // };
  // pair_thing test_b{
  //     .n = "l",
  //     .g = 3,
  //     .m = 1,
  // };
  // bfs_struct test = {.f = 1, .m = 0, .things = {test_a, test_b}};

  pair_thing thulium{
      .n = "a",
      .g = 1,
      .m = 1,
  };
  pair_thing plutonium{
      .n = "b",
      .g = 1,
      .m = 2,
  };
  pair_thing strontium{
      .n = "c",
      .g = 1,
      .m = 2,
  };
  pair_thing promethium{
      .n = "d",
      .g = 3,
      .m = 3,
  };
  pair_thing ruthenium{
      .n = "e",
      .g = 3,
      .m = 3,
  };
  pair_thing elerium{
      .n = "f",
      .g = 1,
      .m = 1,
  };
  pair_thing dilithium{
      .n = "g",
      .g = 1,
      .m = 1,
  };
  bfs_struct as = {.f = 1,
                   .m = 0,
                   .things = {thulium, plutonium, strontium, promethium,
                              ruthenium, elerium, dilithium}};

  // vector<int> locations = {
  //     1, // thulium g
  //     1, // thulium m
  //     1, // plutonium g
  //     2, // plutonium m
  //     1, // strontium g
  //     2, // strontium m
  //     3, // promethium g
  //     3, // promethium m
  //     3, // ruthenium g
  //     3  // ruthenium m
  // };

  // for (auto l : as_ints(locations, 1)) {
  //   cout << l << endl;
  // }
  // exit(1);
  exhaust_it_bfs(as, 4);

  // exhaust_it(locations, 1, 1, 4, 0);
  cout << "shortest: " << shortest << endl;
  // for (auto kv : seen) {
  //   cout << kv.first << " " << kv.second << endl;
  // }

  return 0;
}
