#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <regex>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;
typedef unsigned int ulong;

vector<pair<ulong, ulong>> merge(vector<pair<ulong, ulong>> ranges) {
  vector<pair<ulong, ulong>> cranges{};
  cout << "from: " << ranges.size();

  sort(ranges.begin(), ranges.end(),
       [](auto &left, auto &right) { return left.first < right.first; });

  ulong start = ranges[0].first;
  ulong end = ranges[0].second;
  for (size_t i = 0; i < ranges.size(); i++) {
    if (end + 1 < ranges[i].first) {
      pair<ulong, ulong> nr = make_pair(start, end);
      cranges.push_back(nr);
      start = ranges[i].first;
      end = ranges[i].second;
    } else {
      end = ranges[i].second;
    }
  }
  pair<ulong, ulong> nr = make_pair(start, end);
  cranges.push_back(nr);

  cout << " to: " << cranges.size() << endl;
  return cranges;
}

int main(int argc, char **argv) {
  vector<pair<ulong, ulong>> ranges{};

  regex range_regex("(\\d+)-(\\d+)");
  smatch match;
  ifstream infile(argv[1]);

  for (string line; getline(infile, line);) {
    regex_search(line, match, range_regex);
    pair<ulong, ulong> range = make_pair(stoul(match[1]), stoul(match[2]));
    ranges.push_back(range);
  }

  auto cranges = merge(ranges);
  for (int i = 0; i < 3; i++) {
    cranges = merge(cranges);
  }

  for (auto cr : cranges) {
    ulong mb = cr.second + 1;
    cout << mb << endl;
    bool ok = true;
    for (auto r : ranges) {
      if (r.first < mb && mb < r.second) {
        ok = false;
      }
    }
    if (ok) {
      cout << "yes: " << mb << endl;
      break;
    }
  }

  sort(ranges.begin(), ranges.end(),
       [](auto &left, auto &right) { return left.first < right.first; });

  unsigned long long last_ip = 0;
  unsigned long long total = 0;
  for (auto r : ranges) {
    if (last_ip < r.first) {
      total += (r.first - last_ip);
    }
    last_ip = max(last_ip, (unsigned long long)r.second + 1);
  }
  total += (((long long)numeric_limits<ulong>::max() + 1) - last_ip);
  cout << total << endl;

  return 0;
}
