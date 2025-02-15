#include <climits>
#include <format>
#include <fstream>
#include <iostream>
#include <openssl/evp.h>
#include <optional>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

// imitating https://docs.openssl.org/master/man3/EVP_DigestInit/#notes
// persistence…
string md5(unsigned char *d, unsigned long n) {
  unsigned char md_value[EVP_MAX_MD_SIZE];
  unsigned int md_len;

  EVP_MD_CTX *mdctx = EVP_MD_CTX_new();
  EVP_DigestInit_ex(mdctx, EVP_md5(), NULL);
  EVP_DigestUpdate(mdctx, d, n);
  EVP_DigestFinal_ex(mdctx, md_value, &md_len);
  EVP_MD_CTX_free(mdctx);

  std::stringstream md5_stream{};

  for (unsigned int i = 0; i < md_len; i++) {
    md5_stream << std::format("{:02x}", md_value[i]);
  }
  return md5_stream.str();
}


bool shortest = true;
bool open_char(char c) {
  unordered_set<char> o = {'b', 'c', 'd', 'e', 'f'};
  return o.contains(c);
}

size_t shortest_path = SIZE_T_MAX;
size_t longest_path = 0;

void helper(string passcode, int x, int y, string path) {
  if (x == 3 && y == 3) {
    if (shortest && path.size() < shortest_path) {
      shortest_path = path.size();
      cout << "candidate of length: " << path.size() << endl;
      cout << "\t" << path << endl;

    }
    if (path.size() > longest_path) {
        longest_path = path.size();
    }
    return;
  }
  if (shortest && shortest_path < path.size()) {
    return;
  }
  string s = format("{}{}", passcode, path);
  string hash = md5((unsigned char *)s.data(), s.size());
  if (open_char(hash[0]) && 0 < y) {
    helper(passcode, x, y - 1, path + "U");
  }
  if (open_char(hash[1]) && y < 3) {
    helper(passcode, x, y + 1, path + "D");
  }

  if (open_char(hash[2]) && 0 < x) {
    helper(passcode, x - 1, y, path + "L");
  }

  if (open_char(hash[3]) && x < 3) {
    helper(passcode, x + 1, y, path + "R");
  }
}

int node_rep(int x, int y) { return x * 10 + y; }

int main() {

  helper("help!", 0, 0, "");
  cout << "longest: " << longest_path << endl;

  return 0;
}
