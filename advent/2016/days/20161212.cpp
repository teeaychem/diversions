#include <__format/format_functions.h>
#include <fstream>
#include <iostream>
#include <limits>
#include <map>
#include <optional>
#include <regex>
#include <string>
#include <variant>
#include <vector>

using namespace std;
typedef char r_id;
typedef long long r_val;

struct Inc {
  r_id r;
};

struct Dec {
  r_id r;
};

struct CpyInt {
  r_id r;
  r_val v;
};

struct CpyReg {
  r_id r;
  r_id v;
};

struct JnzInt {
  int c;
  r_val v;
};

struct JnzReg {
  r_id r;
  r_val v;
};

using Instruction = variant<Inc, Dec, CpyInt, CpyReg, JnzInt, JnzReg>;

class Machine {
public:
  map<char, r_val> registers = {{'a', 0}, {'b', 0}, {'c', 1}, {'d', 0}};

  unsigned long long count = 0;
  unsigned long long ptr = 0;
  vector<Instruction> instructions;

  void print() {
    cout << ptr << " - ";
    for (auto p : registers) {
      cout << p.first << " : " << p.second << " - ";
    }
    cout << endl;
  }

  void add_instruction(Instruction i) { instructions.push_back(i); }

  string instruction_string(Instruction current) {
    try {
      Inc i = get<Inc>(current);
      return format("inc {}", i.r);
    } catch (bad_variant_access &e) {
    }

    try {
      Dec i = get<Dec>(current);
      return format("dec {}", i.r);
    } catch (bad_variant_access &e) {
    }

    try {
      CpyInt i = get<CpyInt>(current);
      return format("cpy {} {}", i.v, i.r);
    } catch (bad_variant_access &e) {
    }

    try {
      CpyReg i = get<CpyReg>(current);
      return format("cpy {} {}", i.v, i.r);
    } catch (bad_variant_access &e) {
    }

    try {
      JnzInt i = get<JnzInt>(current);
      return format("jnz {} {}", i.c, i.v);
    } catch (bad_variant_access &e) {
    }

    try {
      JnzReg i = get<JnzReg>(current);
      return format("jnz {} {}", i.r, i.v);
    } catch (bad_variant_access &e) {
    }
    exit(1);
  }

  void print_instructions() {
    for (size_t i = 0; i < instructions.size(); i++) {
      cout << i << " - " << instruction_string(instructions[i]) << endl;
    }
  }

  void exec() {
    Instruction current = instructions[ptr];
    // print_instruction(current);
    if (count % 50000 == 0) {
      print();
    }

    try {
      Inc i = get<Inc>(current);
      registers.at(i.r) += 1;
      ptr += 1;
    } catch (bad_variant_access &e) {
    }

    try {
      Dec i = get<Dec>(current);
      registers.at(i.r) -= 1;
      ptr += 1;
    } catch (bad_variant_access &e) {
    }

    try {
      CpyInt i = get<CpyInt>(current);
      registers.at(i.r) = i.v;
      ptr += 1;
      // todo
    } catch (bad_variant_access &e) {
    }

    try {
      CpyReg i = get<CpyReg>(current);
      registers.at(i.r) = registers.at(i.v);
      ptr += 1;
      // todo
    } catch (bad_variant_access &e) {
    }

    try {
      JnzInt i = get<JnzInt>(current);
      if (i.c != 0) {
        ptr += i.v;
      } else {
        ptr += 1;
      }
      // todo
    } catch (bad_variant_access &e) {
    }

    try {
      JnzReg i = get<JnzReg>(current);
      if (registers.at(i.r) != 0) {
        ptr += i.v;
      } else {
        ptr += 1;
      }
      // todo
    } catch (bad_variant_access &e) {
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
      }
    }
  }
};

int main(int _argc, char **argv) {
  Machine machine{};

  regex inc_regex("inc ([a-z])");
  regex dec_regex("dec ([a-z])");
  regex cpy_int_regex("cpy ((?:\\+|-)?\\d+) ([a-z])");
  regex cpy_reg_regex("cpy ([a-z]) ([a-z])");
  regex jnz_int_regex("jnz ((?:\\+|-)?\\d+) ((?:\\+|-)?\\d+)");
  regex jnz_reg_regex("jnz ([a-z]) ((?:\\+|-)?\\d+)");
  smatch matches;

  ifstream infile(argv[1]);
  for (string line; getline(infile, line);) {
    if (regex_match(line, matches, inc_regex)) {
      r_id reg = matches[1].str()[0];
      machine.add_instruction(Inc{reg});
      continue;
    }

    if (regex_match(line, matches, dec_regex)) {
      r_id reg = matches[1].str()[0];
      machine.add_instruction(Dec{reg});
      continue;
    }

    if (regex_match(line, matches, cpy_int_regex)) {
      r_id reg = matches[2].str()[0];
      r_val val = stoi(matches[1]);
      machine.add_instruction(CpyInt{.r = reg, .v = val});
      continue;
    }

    if (regex_match(line, matches, cpy_reg_regex)) {
      r_id reg = matches[2].str()[0];
      r_id val = matches[1].str()[0];
      machine.add_instruction(CpyReg{.r = reg, .v = val});
      continue;
    }

    if (regex_match(line, matches, jnz_int_regex)) {
      int check = stoi(matches[1]);
      r_val val = stoi(matches[2]);
      machine.add_instruction(JnzInt{.c = check, .v = val});
      continue;
    }

    if (regex_match(line, matches, jnz_reg_regex)) {
      r_id reg = matches[1].str()[0];
      r_val val = stoi(matches[2]);
      machine.add_instruction(JnzReg{.r = reg, .v = val});
      continue;
    }

    cout << "?? " << line << endl;
  }
  machine.print_instructions();

  machine.run();
  machine.print();

  return 0;
}
