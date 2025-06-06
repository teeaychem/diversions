#include <__format/format_functions.h>
#include <cassert>
#include <climits>
#include <fstream>
#include <iostream>
#include <limits>
#include <map>
#include <optional>
#include <regex>
#include <stdexcept>
#include <string>
#include <unordered_set>
#include <variant>
#include <vector>

using namespace std;
typedef char r_id;
typedef long long r_val;

struct Instruction {
  string inst;
  string a;
  string b;
};

bool is_register(string s) {
  static unordered_set<char> rs = {'a', 'b', 'c', 'd'};
  return s.size() == 1 && rs.contains(s[0]);
}

class Machine {
public:
  map<char, r_val> registers = {{'a', 0}, {'b', 0}, {'c', 0}, {'d', 0}};

  unsigned long long count = 0;
  unsigned long long ptr = 0;
  vector<Instruction> instructions;
  string tape{};

  void print() {
    cout << ptr << " - ";
    for (auto p : registers) {
      cout << p.first << " : " << p.second << " - ";
    }
    cout << endl;
  }

  void add_instruction(Instruction i) { instructions.push_back(i); }

  string instruction_string(Instruction i) {
    return format("{} {} {}", i.inst, i.a, i.b);
    exit(1);
  }

  void print_instructions() {
    for (size_t i = 0; i < instructions.size(); i++) {
      cout << i << " - " << instruction_string(instructions[i]) << endl;
    }
  }

  void exec() {
    Instruction i = instructions[ptr];

    if (false) {
      print_instructions();
      cout << endl << endl;
      cout << ptr << " - " << instruction_string(instructions[ptr]) << endl;
    }

    if (count % 500000 == 0) {
      print(); //
    }

    if (i.inst == "out") {
      cout << "out" << endl;
      try {
        tape.push_back(stoi(i.a));
      } catch (invalid_argument &e) {
        if (is_register(i.a)) {
          tape.push_back(registers.at(i.a[0]));
        } else {
          exit(423);
        }
      }

      if (is_register(i.a)) {
        registers.at(i.a[0]) += 1;
      }
      ptr += 1;

    }

    else if (i.inst == "inc") {

      if (is_register(i.a)) {
        registers.at(i.a[0]) += 1;
      }
      ptr += 1;

    } else if (i.inst == "dec") {

      if (is_register(i.a)) {
        registers.at(i.a[0]) -= 1;
      }
      ptr += 1;

    } else if (i.inst == "tgl") {

      int toggle_at = ptr;
      try {
        toggle_at += stoi(i.a);
      } catch (invalid_argument &e) {
        if (is_register(i.a)) {
          toggle_at += registers.at(i.a[0]);
        } else {
          exit(423);
        }
      }

      // cout << "TGL " << i.a << ", " << ptr << ", " << toggle_at << endl;

      if (toggle_at < instructions.size()) {

        auto other = &instructions[toggle_at];
        if (other->inst == "inc") {
          other->inst = "dec";
        } else if (other->inst == "dec" || other->inst == "tgl" ||
                   other->inst == "out") {
          other->inst = "inc";
        } else if (other->inst == "jnz") {
          other->inst = "cpy";
        } else if (other->inst == "cpy") {
          other->inst = "jnz";
        } else {
          cout << "ff: " << other->inst << endl;
          exit(234);
        }
      }

      ptr += 1;

    } else if (i.inst == "cpy") {

      if (is_register(i.b)) {
        try {
          int j = stoi(i.a);
          registers.at(i.b[0]) = j;
        } catch (invalid_argument &e) {
          if (is_register(i.a)) {
            registers.at(i.b[0]) = registers.at(i.a[0]);
          } else {
            exit(423);
          }
        }
      }
      ptr += 1;

    } else if (i.inst == "jnz") {

      int test;
      try {
        test = stoi(i.a);
      } catch (invalid_argument &e) {
        if (is_register(i.a)) {
          test = registers.at(i.a[0]);
        } else {
          exit(1);
        }
      }

      int go_to;
      try {
        go_to = stoi(i.b);
      } catch (invalid_argument &e) {
        if (is_register(i.b)) {
          go_to = registers.at(i.b[0]);
        } else {
          exit(1);
        }
      }

      if (test != 0) {
        ptr += go_to;
      } else {
        ptr += 1;
      };
    } else {

      cout << "unknown " << i.inst << endl;
    }

    count += 1;
  }

  void run() {
    while (true) {
      // print();
      exec();
      if (ptr >= instructions.size()) {
        cout << "break " << ptr << endl;
        break;
      } else {
        cout << tape << endl;
        for (size_t i = 0; i < tape.size(); i++) {
          if (i % 2 != 0) {
            if (tape[i] != '1') {
              break;
            }
          } else {
            if (tape[i] != '0') {
              break;
            }
          }
        }
      }
    }
  }
};

void try_it(int a) {
  string tape{};
  int count = 0;
  int d = a;
  int c = 14;
  int b;
  while (c != 0) {
    int b = 182;
    while (b != 0) {
      d += 1;
      b -= 1;
    }
    c -= 1;
  }
  while (true) {
    a = d;
    while (a != 0) {
      b = a;
      a = 0;
      c = 2;
      if (c != 0) {
        while (b != 0) {
          b -= 1;
          c -= 1;
          if (c == 0) {
            a += 1;
            c = 2;
          }
        }
      }
      b = 2;
      while (c != 0) {
        b -= 1;
        c -= 1;
      }
      if (count % 2 != 0) {
        if (b != 1) {
          cout << "fail: " << tape << endl;
          return;
        }
      } else {
        if (b != 0) {
          cout << "fail: " << tape << endl;
          return;
        }
      }
      tape.push_back(b);
      count += 1;
    }
  }
}

int main(int _argc, char **argv) {
  // Machine machine{};

  // regex one_regex("([a-z]+) ((?:\\+|-)?\\d+|[a-z])");
  // regex two_regex("([a-z]+) ((?:\\+|-)?\\d+|[a-z]) ((?:\\+|-)?\\d+|[a-z])");
  // smatch matches;

  // ifstream infile(argv[1]);
  // for (string line; getline(infile, line);) {
  //   if (regex_match(line, matches, one_regex)) {
  //     machine.add_instruction(
  //         Instruction{.inst = matches[1], .a = matches[2], .b = "-"});
  //     continue;
  //   }

  //   if (regex_match(line, matches, two_regex)) {

  //     machine.add_instruction(
  //         Instruction{.inst = matches[1], .a = matches[2], .b = matches[3]});
  //     continue;
  //   }

  //   cout << "?? " << line << endl;
  // }
  // // machine.print_instructions();
  // machine.registers['a'] = 1;
  // machine.run();
  // machine.print();

  for (int a = 0; a < INT_MAX; a++) {
    cout << "trying: " << a << endl;
    try_it(a);
  }

  return 0;
}
