#include <advent/strings.hpp>
#include <format>
#include <fstream>
#include <iostream>
#include <openssl/evp.h>
#include <optional>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;
using namespace advent::string;

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

void pv(vector<optional<char>> &v) {
  for (auto c : v) {
    cout << c.value_or('.');
  }
  cout << endl;
}

string stretch(string &h, int i) {
  string stretched = h;
  for (int j = 0; j < i; j++) {
    string past = stretched;
    stretched = md5((unsigned char *)past.data(), past.size());
  }
  return stretched;
}

void part_one(string salt) {
  vector<string> passwords{};
  for (int i = 0; i < INT_MAX; i++) {
    string three_string = format("{}{}", salt, i);
    string three_hash =
        md5((unsigned char *)three_string.data(), three_string.size());

    optional<char> three_char = first_consecutive_char(three_hash, 3);
    if (three_char.has_value()) {
      for (int j = 1; j <= 1000; j++) {
        string five_string = format("{}{}", salt, i + j);
        string five_hash =
            md5((unsigned char *)five_string.data(), five_string.size());

        if (c_in_a_row(five_hash, three_char.value(), 5)) {
          passwords.push_back(three_hash);
          cout << passwords.size() << " (" << i << ") " << three_hash << endl;
          break;
        }
      }
    }
    if (passwords.size() == 64) {
      break;
    }
  }
}

void write_hashes(string salt, int i) {
  fstream file;
  int j = 0;
  file.open("hashes.txt", ios::in | ios::binary);
  for (string line; getline(file, line);) {
    j++;
  }
  file.close();

  file.open("hashes.txt", std::ios_base::app);
  // time for a walk
  for (; j < i; j++) {
    string three_string = format("{}{}", salt, j);
    string three_hash = stretch(three_string, 2017);
    file << three_hash << endl;
    if (j % 100 == 0) {
      cout << j << endl;
    }
  }
  file.close();
}

void part_two(string salt) {
  vector<string> hashes{};
  fstream file;
  file.open("hashes.txt", ios::in | ios::binary);
  for (string line; getline(file, line);) {
    hashes.push_back(line);
  }

  vector<string> passwords{};
  for (int i = 0; i < INT_MAX; i++) {
    string three_hash = hashes[i];

    optional<char> three_char = first_consecutive_char(three_hash, 3);
    if (three_char.has_value()) {
      cout << "\t!" << i << " " << three_hash << endl;
      for (int j = 1; j <= 1000; j++) {
        string five_hash = hashes[i + j];

        if (c_in_a_row(five_hash, three_char.value(), 5)) {
          passwords.push_back(three_hash);
          cout << passwords.size() << " (" << i << ") " << three_hash << endl;
          break;
        }
      }
    }
    if (passwords.size() == 64) {
      break;
    }
  }
}

int main() {
  string salt = "abc";
  // part_one(salt);
  write_hashes(salt, 1);
  part_two(salt);
  // cout << stretch(x, 3);

  //
  // cout << md5((unsigned char *)test_one.data(), test_one.size());
  // part_one();
  // // part_two();
  return 0;
}
