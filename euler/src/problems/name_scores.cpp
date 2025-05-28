#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

void name_scores(ifstream &infile) {

  vector<pair<string, size_t>> names{};
  names.reserve(5000);

  char c;
  string name_buffer{};
  size_t name_sum{0};

  while (infile >> c) {
    if (c == '"') {
      continue;
    } else if (c == ',') {
      string complete_name = name_buffer;

      names.push_back(make_pair(complete_name, name_sum));
      name_buffer.clear();
      name_sum = 0;

    } else {
      name_buffer.push_back(c);
      name_sum += c - 'A' + 1;
    }
  }
  names.push_back(make_pair(name_buffer, name_sum));

  sort(names.begin(), names.end(),
       [](pair<string, size_t> const &a, pair<string, size_t> const &b) {
         return a.first < b.first;
       });

  size_t big_sum{0};

  for (int i = 0; i < names.size(); ++i) {
    big_sum += names[i].second * (i + 1);
  }

  cout << big_sum << "\n";
}
