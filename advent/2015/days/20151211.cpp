#include <iostream>
#include <optional>
using namespace std;

string the_next(string current) {
  if (current.empty()) {
    return "a";
  } else {
    for (size_t i = current.size(); i > 0; --i) {
      if (current[i - 1] < 'z') {
        current[i - 1] = (char)(current[i - 1] + 1);
        for (size_t j = i; j < current.size(); j++) {
          current[j] = 'a';
        }
        return current;
      }
    }
  }
  return string(current.size() + 1, 'a');
}

bool password_ok(string password) {
  if (password.size() < 4) {
    return false;
  }

  if (password.contains('i') || password.contains('l') ||
      password.contains('o')) {
    return false;
  }

  optional<char> pair_one = nullopt;
  optional<char> pair_two = nullopt;
  for (size_t i = 0; i < password.size() - 1; i++) {
    if (password[i] == password[i + 1]) {
      if (pair_one == nullopt) {
        pair_one = password[i];
      } else if (password[i] != pair_one) {
        pair_two = password[i];
      }
    }
  }
  if (pair_one == nullopt || pair_two == nullopt) {
    return false;
  }
  bool increasing_triple = false;
  for (size_t i = 0; i < password.size() - 2; i++) {
    if (password[i] + 1 == password[i + 1] &&
        password[i + 1] + 1 == password[i + 2]) {
      increasing_triple = true;
      break;
    }
  }
  if (!increasing_triple) {
    return false;
  }

  return true;
}

int main() {

  string password = "password";
  password = the_next(password);
  while (!password_ok(password)) {
    password = the_next(password);
  }

  cout << "? " << password << endl;

  return 0;
}
