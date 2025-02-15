
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

void next_dragon(vector<bool> &current_dragon) {
  current_dragon.push_back(false);
  for (size_t i = current_dragon.size() - 1; 0 < i; --i) {
    current_dragon.push_back(!current_dragon[i - 1]);
  }
}

string bool_string(vector<bool> &v) {
  stringstream ss{};
  for (size_t i = 0; i < v.size(); i++) {
    ss << (v[i] ? '1' : '0');
  }
  return ss.str();
}

vector<bool> as_bools(string &s) {
  vector<bool> v{};
  for (size_t i = 0; i < s.size(); i++) {
    v.push_back(s[i] == '1' ? true : false);
  }
  return v;
}

vector<bool> checksum_step(vector<bool> &v) {
  vector<bool> c{};
  for (size_t i = 0; i < v.size(); i += 2) {
    c.push_back(v[i] == v[i + 1]);
  }
  return c;
}

vector<bool> checksum(vector<bool> &v) {
  vector<bool> c = checksum_step(v);
  while ((c.size() % 2) == 0) {
    c = checksum_step(c);
  }

  return c;
}

vector<bool> fill(string &s, size_t c) {
  vector<bool> v = as_bools(s);
  while (v.size() < c) {
    next_dragon(v);
  }
  v.erase(v.begin() + c, v.end());
  return v;
}

int main(int argc, char **argv) {

  string s = "101";
  auto data = fill(s, 2);
  // cout << bool_string(data) << endl;

  auto csum = checksum(data);
  auto csum_s = bool_string(csum);

  // cout << csum_s << " : " << bool_string(data) << endl;
  cout << csum_s << endl;
  return 0;
}
