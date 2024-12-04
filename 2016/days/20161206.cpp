#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main(int argc, char **argv) {

  int msg_length = 8;
  vector<vector<pair<char, int>>> index_vec{};
  for (int i = 0; i < msg_length; i++) {
    vector<pair<char, int>> v{};
    index_vec.push_back(v);
  }

  ifstream infile(argv[1]);
  for (string line; getline(infile, line);) {
    for (int i = 0; i < msg_length; i++) {
      char c = line[i];
      auto it = find_if(index_vec[i].begin(), index_vec[i].end(),
                        [&c](pair<char, int> &e) { return e.first == c; });
      if (it == index_vec[i].end()) {
        index_vec[i].push_back(pair(c, 1));
      } else {
        it->second = it->second + 1;
      }
    }
  }

  for (size_t i = 0; i < index_vec.size(); i++) {
    // switch the comparison for part two
    sort(index_vec[i].begin(), index_vec[i].end(),
         [](auto &l, auto &r) { return l.second < r.second; });
  }
  for (auto iv : index_vec) {
    for (auto x : iv) {
      cout << x.first << " " << x.second << " ";
    }
    cout << endl;
  }

  for (auto iv : index_vec) {
    cout << iv[0].first;
  }
  cout << endl;

  return 0;
}
