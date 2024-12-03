#include <format>
#include <iostream>
#include <openssl/evp.h>
#include <optional>
#include <sstream>
#include <string>
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
  md5_stream << std::endl;
  return md5_stream.str();
}

void pv(vector<optional<char>> &v) {
  for (auto c : v) {
    cout << c.value_or('.');
  }
  cout << endl;
}

string door_id = "cxdnnyjw";
int zeros = 5; // 6 for part two
string zero_string = string(zeros, '0');

void part_one() {
  string the_password{};
  for (int i = 0; i < INT_MAX; i++) {
    string the_string = format("{}{}", door_id, i);

    string md5_hash =
        md5((unsigned char *)the_string.data(), the_string.size());

    if (md5_hash.substr(0, zeros) == zero_string) {
      cout << md5_hash[zeros] << endl;
      the_password.push_back(md5_hash[zeros]);
      if (the_password.size() == 8) {
        break;
      }
    }

    if (i % 100000 == 0) {
      cout << "passed: " << i << endl;
    }
  }
  cout << ": " << the_password << endl;
}

void part_two() {
  vector<optional<char>> password_vec{};
  for (int i = 0; i < 8; i++) {
    password_vec.push_back(nullopt);
  }

  string zero_string = string(zeros, '0');

  for (int i = 0; i < INT_MAX; i++) {
    string the_string = format("{}{}", door_id, i);

    string md5_hash =
        md5((unsigned char *)the_string.data(), the_string.size());

    if (md5_hash.substr(0, zeros) == zero_string) {
      cout << md5_hash[zeros] << endl;
      try {
        int insert_at = stoi(md5_hash.substr(zeros, 1));
        if (0 <= insert_at && insert_at < 8) {
          if (!password_vec[insert_at].has_value()) {
            password_vec[insert_at] = md5_hash[zeros + 1];
          }
        }
        pv(password_vec);
      } catch (invalid_argument) {
      }

      bool finished = true;
      for (int i = 0; i < 8; i++) {
        if (!password_vec[i].has_value()) {
          finished = false;
          break;
        }
      }
      if (finished) {
        cout << "over: " << endl;
        pv(password_vec);
        return;
      }
    }

    if (i % 100000 == 0) {
      cout << "passed: " << i << endl;
    }
  }
}

int main() {
  string test_one = "abc3231929";
  cout << md5((unsigned char *)test_one.data(), test_one.size());
  part_one();
  // part_two();
  return 0;
}
