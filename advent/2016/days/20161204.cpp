
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <optional>
#include <regex>
#include <stdexcept>
#include <string>
#include <unordered_map>
using namespace std;

optional<int> check_string(string s) {
  regex r("(:?([a-z]+))|([0-9]+)|(\\[[a-z]+\\])");
  regex_iterator<string::iterator> regex_end;

  unordered_map<char, int> count_map{};

  regex_iterator<string::iterator> it(s.begin(), s.end(), r);

  int id;
  string chk;

  while (it != regex_end) {
    string part = it->str();
    try {
      id = stoi(part);
      it++;
      continue;
    } catch (invalid_argument) {
    }

    if (part[0] == '[') {
      chk = part.substr(1, part.size() - 2);
      it++;
      continue;
    }

    for (char c : part) {
      try {
        count_map.at(c) += 1;
      } catch (out_of_range) {
        count_map.insert({c, 1});
      }
    }
    it++;
  }

  int last_chk_count;
  try {
    last_chk_count = count_map.at(chk[0]);
  } catch (out_of_range) {
    return nullopt;
  }
  for (size_t i = 1; i < chk.size(); i++) {
    int this_chk_count;
    try {
      this_chk_count = count_map.at(chk[i]);
    } catch (out_of_range) {
      return nullopt;
    }
    if ((this_chk_count < last_chk_count) ||
        (this_chk_count == last_chk_count && chk[i - 1] < chk[i])) {
      last_chk_count = this_chk_count;
    } else {
      return nullopt;
    }
  }
  return id;
}

string decrypt(string s, int k) {
  static string basic = "abcdefghijklmnopqrstuvwxyz";
  string out;

  for (auto c : s) {

    if (0 <= (int)c - 48 && (int)c - 48 <= 9) {
      break;
    }
    if (c == '-') {
      out.push_back(' ');
    } else {
      int l = basic.find(c);
      out.push_back(basic[(l + k) % 26]);
    }
  }
  return out;
}

int main(int argc, char **argv) {

  vector<string> tests = {
      "aaaaa-bbb-z-y-x-123[abxyz]", "a-b-c-d-e-f-g-h-987[abcde]",
      "not-a-real-room-404[oarel]", "totally-real-room-200[decoy]"};

  decrypt("qzmt-zixmtkozy-ivhz", 343);

  int id_sum{0};
  ifstream infile(argv[1]);
  for (string line; getline(infile, line);) {
    int id;
    try {
      id = check_string(line).value();
      id_sum += id;
      cout << id << " - " << decrypt(line, id) << endl;
    } catch (bad_optional_access) {
    }
  }
  cout << "total: " << id_sum << endl;

  return 0;
}
