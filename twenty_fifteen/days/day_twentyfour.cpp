#include <advent/combinatorics.hpp>
#include <cstddef>
#include <iostream>
#include <limits>
#include <ostream>
#include <vector>
using namespace std;

template <typename element> void print_vec(vector<element> &v) {
  for (auto e : v) {
    cout << e << " ";
  }
  cout << endl;
}

template <typename element> element sum_vec(vector<element> &v) {
  element total{};
  for (auto e : v) {
    total += e;
  }
  return total;
}

long int mul_int_vec(vector<int> &v) {
  long int total = 1;
  for (auto e : v) {
    total *= e;
  }
  return total;
}

template <typename element>
void split_vec_helper(vector<vector<vector<element>>> &the_vecs,
                      vector<element> &v, int k, size_t p,
                      vector<vector<element>> buff) {
  if (p == v.size()) {
    the_vecs.push_back(buff);
  } else {
    for (int i = 0; i < k; i++) {
      vector<vector<element>> buff_i = buff;
      buff_i[i].push_back(v[p]);
      split_vec_helper(the_vecs, v, k, p + 1, buff_i);
    }
  }
}

template <typename element>
vector<vector<vector<element>>> split_vec(vector<element> &v, int k) {
  vector<vector<element>> k_empty = {};
  for (int i = 0; i < k; i++) {
    vector<element> empty{};
    k_empty.push_back(empty);
  }
  vector<vector<vector<element>>> the_vecs = {};
  the_vecs.push_back(k_empty);

  vector<vector<element>> buff = {};
  for (int i = 0; i < k; i++) {
    vector<element> empty{};
    buff.push_back(empty);
  }

  split_vec_helper(the_vecs, v, k, 0, buff);
  return the_vecs;
}

template <typename element>
bool equal_splits_helper(vector<element> &v, int k, size_t p, int r,
                         vector<vector<element>> &buff) {
  if (p == v.size()) {
    unordered_set<int> sums{};
    for (auto split : buff) {
      sums.insert(sum_vec(split));
    }
    return sums.size() == 1;
  } else {
    for (int i = 0; i < k; i++) {
      buff[i].push_back(v[p]);
      if (sum_vec(buff[i]) <= r && equal_splits_helper(v, k, p + 1, r, buff)) {
        return true;
      }
      buff[i].pop_back();
    }
    return false;
  }
}

template <typename element> bool equal_splits(vector<element> &v, int k) {
  if (sum_vec(v) % k != 0) {
    return false;
  }

  vector<vector<element>> buff = {};
  for (int i = 0; i < k; i++) {
    vector<element> empty{};
    buff.push_back(empty);
  }
  int required = sum_vec(v) / k;
  return equal_splits_helper(v, k, 0, required, buff);
}

int main(int argc, char **argv) {

  vector<int> packages = {1, 2, 3, 4, 5, 7, 8, 9, 10, 11};
  unordered_set<int> package_set =
      unordered_set(packages.begin(), packages.end());

  int total_package_weight = sum_vec(packages);
  cout << "tpw: " << total_package_weight << endl;
  int locations = 3;
  int required_weight = total_package_weight / locations;
  cout << "rw: " << required_weight << endl;

  vector<vector<int>> candidates{};

  for (size_t i = 0; i < packages.size(); i++) {
    cout << "searching " << i << endl;
    auto f_options = advent::combinatorics::size_k_vectors(packages, i);
    bool ship_it = false;
    for (size_t f_idx = 0; f_idx < f_options.size(); f_idx++) {
      int the_sum = sum_vec(f_options[f_idx]);

      if (the_sum == required_weight) {

        unordered_set<int> remaing_set = package_set;
        for (auto in_front : f_options[f_idx]) {
          remaing_set.extract(in_front);
        }

        vector<int> remaining(remaing_set.begin(), remaing_set.end());

        print_vec(f_options[f_idx]);
        print_vec(remaining);
        cout << "---" << endl;

        if (equal_splits(remaining, locations - 1)) {
          vector<int> c = f_options[f_idx];
          cout << "candidate: " << mul_int_vec(c);
          print_vec(c);
          candidates.push_back(c);
          print_vec(f_options[f_idx]);
          ship_it = true;
        }
      }
    }
    if (ship_it) {
      break;
    }
  }

  cout << "ok" << endl;
  vector<long int> entanglements{};
  for (auto c : candidates) {
    cout << mul_int_vec(c) << " from ";
    print_vec(c);
    entanglements.push_back(mul_int_vec(c));
  }
  long int min = numeric_limits<long int>::max();
  for (auto e : entanglements) {
    if (e < min) {
      min = e;
    }
  }
  cout << "min e: " << min << endl;

  return 0;
}
