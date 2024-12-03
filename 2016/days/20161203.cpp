#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <vector>
using namespace std;

void part_one(ifstream &is) {
  uint ok_count{0};
  uint triangle_count{0};

  regex triple_regex("\\s+(\\d+)\\s+(\\d+)\\s+(\\d+)");
  smatch sm;

  for (string line; getline(is, line);) {
    if (regex_match(line, sm, triple_regex)) {
      int a = stoi(sm[1]);
      int b = stoi(sm[2]);
      int c = stoi(sm[3]);
      if (a + b > c && b + c > a && a + c > b) {
        ok_count += 1;
      }
      triangle_count += 1;
    }
  }
  cout << "ok: " << ok_count << " (" << (float)ok_count / triangle_count << ")"
       << endl;
}

void part_two(ifstream &is) {

  uint ok_count{0};
  uint triangle_count{0};

  vector<vector<int>> triangles{};

  regex i_regex("\\s+(\\d+)");
  smatch sm;

  bool fresh = true;
  int lc{0};
  int idx{0};
  regex_token_iterator<string::iterator> regex_end;
  for (string line; getline(is, line);) {

    regex_token_iterator<string::iterator> ix(line.begin(), line.end(),
                                              i_regex);
    while (ix != regex_end) {
      int x = stoi(*ix);
      if (fresh) {
        vector<int> t{x};
        triangles.push_back(t);
      } else {
        triangles[idx].push_back(x);
      }
      idx++;
      ix++;
    }

    idx = 0;
    lc++;

    if (lc % 3 == 0) {
      for (auto sm : triangles) {
        int a = sm[0];
        int b = sm[1];
        int c = sm[2];
        if (a + b > c && b + c > a && a + c > b) {
          ok_count += 1;
        }
        triangle_count += 1;
      }
      triangles.clear();
      fresh = true;
    } else {
      fresh = false;
    }
  }

  cout << "ok: " << ok_count << " (" << (float)ok_count / triangle_count << ")"
       << endl;
}

int main(int argc, char **argv) {

  ifstream infile(argv[1]);
  part_two(infile);

  return 0;
}
