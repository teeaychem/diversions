#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <vector>
using namespace std;

bool tls_idx(string &s, int i) {
  bool different = s[i] != s[i + 1];
  bool outer_match = s[i] == s[i + 3];
  bool inner_match = s[i + 1] == s[i + 2];

  return different && outer_match && inner_match;
}

bool tls(string &s) {
  for (size_t i = 0; i < s.size() - 3; i++) {
    if (tls_idx(s, i)) {
      return true;
    }
  }
  return false;
}

bool aba_bab_idx(string &s, int i) {
  bool different = s[i] != s[i + 1];
  bool match = s[i] == s[i + 2];

  return different && match;
}

vector<string> aba_babs(string &s) {
  vector<string> x_x{};
  for (size_t i = 0; i < s.size() - 2; i++) {
    if (aba_bab_idx(s, i)) {
      string x_o = s.substr(i, 3);
      x_x.push_back(x_o);
    }
  }
  return x_x;
}

bool ssl(string &addr) {
  vector<string> abas{};
  vector<string> babs{};

  // cout << "testing: " << addr << endl;
  regex lol("\\[([a-z]+)\\]");
  smatch lol_m;
  auto regex_end = sregex_iterator();
  auto lol_plus = sregex_iterator(addr.begin(), addr.end(), lol);

  // cout << "hypernet sequences: " << endl;
  for (auto lol_i = lol_plus; lol_i != regex_end; lol_i++) {
    string x_x = lol_i->str().substr(1, lol_i->str().size() - 2);
    auto ugh = aba_babs(x_x);
    for (auto uff : ugh) {
      babs.push_back(uff);
    }
  }

  regex ffs("\\]([a-z]+)|(^[a-z][a-z]*)");
  smatch ffs_m;
  auto ffs_plus = sregex_iterator(addr.begin(), addr.end(), ffs);

  // cout << "the rest: " << endl;
  for (auto ffs_i = ffs_plus; ffs_i != regex_end; ffs_i++) {
    string x_o = ffs_i->str();
    if (x_o[0] == ']') {
      x_o = x_o.substr(1, ffs_i->str().size() - 1);
    }
    auto barg = aba_babs(x_o);
    for (auto bov : barg) {
      abas.push_back(bov);
    }
  }
  for (auto aba : abas) {
    for (auto bab : babs) {
      if (aba[0] == bab[1] && aba[1] == bab[0]) {
        return true;
      }
    }
  }
  return false;
}

// bool addr_ok(string &addr) {
//   int left_brace = addr.find('[');
//   int right_brace = addr.find(']');
//   string hypernet = addr.substr(left_brace + 1, (right_brace - left_brace) -
//   1); if (mirror(hypernet)) {
//     return false;
//   }
//   string left = addr.substr(0, left_brace);
//   string right = addr.substr(right_brace + 1, addr.size() - right_brace);
//   return mirror(left) || mirror(right);
// }

bool addr_ok(string &addr) {
  cout << "testing: " << addr << endl;
  regex lol("\\[([a-z]+)\\]");
  smatch lol_m;
  auto regex_end = sregex_iterator();
  auto lol_plus = sregex_iterator(addr.begin(), addr.end(), lol);

  cout << "hypernet sequences: " << endl;
  for (auto lol_i = lol_plus; lol_i != regex_end; lol_i++) {
    string x_x = lol_i->str().substr(1, lol_i->str().size() - 2);
    cout << x_x << endl;
    if (tls(x_x)) {
      return false;
    }
  }

  regex ffs("\\]([a-z]+)|(^[a-z][a-z]*)");
  smatch ffs_m;
  auto ffs_plus = sregex_iterator(addr.begin(), addr.end(), ffs);

  cout << "the rest: " << endl;
  for (auto ffs_i = ffs_plus; ffs_i != regex_end; ffs_i++) {
    string x_o = ffs_i->str();
    if (x_o[0] == ']') {
      x_o = x_o.substr(1, ffs_i->str().size() - 1);
    }
    cout << x_o << endl;
    if (tls(x_o)) {
      return true;
    }
  }
  return false;
}

int main(int argc, char **argv) {

  auto tests = {"abba[mnop]qrst", "abcd[bddb]xyyx", "aaaa[qwer]tyui",
                "ioxxoj[asdfgh]zxcvbn"};
  for (string test : tests) {
    cout << test << " : " << addr_ok(test) << endl;
  }

  ifstream infile(argv[1]);
  int uf{0};
  int pp{0};
  for (string line; getline(infile, line);) {
    if (addr_ok(line)) {
      uf += 1;
    }
    if (ssl(line)) {
      pp += 1;
    }
  }
  cout << uf << endl;
  cout << pp << endl;

  return 0;
}
