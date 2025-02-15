#include <format>
#include <iostream>
#include <openssl/evp.h>
#include <sstream>
#include <string>

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

int main() {
  string test_one = "abcdef609043";
  cout << md5((unsigned char *)test_one.data(), test_one.size());

  int zeros = 5; // 6 for part two

  std::string secret_key = "secret!"; // oops

  for (int i = 0; i < INT_MAX; i++) {
    string the_string = std::format("{}{}", secret_key, i);

    string md5_hash =
        md5((unsigned char *)the_string.data(), the_string.size());
    if (md5_hash.substr(0, zeros) == string(zeros, '0')) {
      cout << "match: " << i << endl;
      break;
    }

    if (i % 100000 == 0) {
      cout << "passed: " << i << endl;
    }
  }

  return 0;
}
