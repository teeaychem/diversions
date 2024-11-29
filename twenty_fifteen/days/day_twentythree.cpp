#include <fstream>
#include <iostream>
#include <regex>
#include <variant>
#include <vector>

using namespace std;

struct Hlf {
  uint r;
};
struct Tpl {
  uint r;
};
struct Inc {
  uint r;
};
struct Jmp {
  int j;
};
struct Jie {
  uint r;
  int j;
};
struct Jio {
  uint r;
  int j;
};
using Instruction = variant<Hlf, Tpl, Inc, Jmp, Jie, Jio>;

class Machine {
public:
  vector<uint> registers = {1, 0};

  uint ptr = 0;
  vector<Instruction> instructions;

  void print() {
    cout << ptr << " - ";
    for (uint i = 0; i < registers.size(); i++) {
      cout << registers[i] << " ";
    }
    cout << endl;
  }

  void add_instruction(Instruction i) { instructions.push_back(i); }

  void print_instruction(Instruction current) {
    try {
      Hlf h = get<Hlf>(current);
      cout << "hlf " << h.r << " " << endl;
    } catch (bad_variant_access &e) {
    }

    try {
      Tpl h = get<Tpl>(current);
      cout << "tpl " << h.r << endl;
    } catch (bad_variant_access &e) {
    }

    try {
      Inc i = get<Inc>(current);
      cout << "inc " << i.r << endl;
    } catch (bad_variant_access &e) {
    }

    try {
      Jmp j = get<Jmp>(current);
      cout << "jmp " << j.j << endl;
    } catch (bad_variant_access &e) {
    }

    try {
      Jie j = get<Jie>(current);
      cout << "jie " << j.r << " " << j.j << endl;
    } catch (bad_variant_access &e) {
    }

    try {
      Jio j = get<Jio>(current);
      cout << "jio " << j.r << " " << j.j << endl;
    } catch (bad_variant_access &e) {
    }
  }

  void exec() {
    Instruction current = instructions[ptr];

    try {
      Hlf h = get<Hlf>(current);
      registers[h.r] /= 2;
      ptr += 1;
    } catch (bad_variant_access &e) {
    }

    try {
      Tpl h = get<Tpl>(current);
      registers[h.r] *= 3;
      ptr += 1;
    } catch (bad_variant_access &e) {
    }

    try {
      Inc i = get<Inc>(current);
      registers[i.r] += 1;
      ptr += 1;
    } catch (bad_variant_access &e) {
    }

    try {
      Jmp j = get<Jmp>(current);
      ptr += j.j;
    } catch (bad_variant_access &e) {
    }

    try {
      Jie j = get<Jie>(current);
      if (registers[j.r] % 2 == 0) {
        ptr += j.j;
      } else {
        ptr += 1;
      }
    } catch (bad_variant_access &e) {
    }

    try {
      Jio j = get<Jio>(current);
      if (registers[j.r] == 1) {
        ptr += j.j;
      } else {
        ptr += 1;
      }
    } catch (bad_variant_access &e) {
    }
  }

  void run() {
    while (true) {
      // print();
      exec();
      if (ptr >= instructions.size()) {
        break;
      }
    }
  }
};

uint string_to_register(string s) {
  if (s == "a") {
    return 0;
  } else if (s == "b") {
    return 1;
  } else {
    cout << "Unknown register" << endl;
    exit(1);
  }
}

int main(int _argc, char **argv) {
  // Machine test_machine{};
  // test_machine.add_instruction(Inc{0});
  // test_machine.add_instruction(Jio{0, 2});
  // test_machine.add_instruction(Tpl{0});
  // test_machine.add_instruction(Inc{0});
  // test_machine.run();
  // test_machine.print();

  Machine machine{};

  regex register_regex("(hlf|tpl|inc) (a|b)");
  regex jmp_regex("jmp ((?:\\+|-)\\d+)");
  regex jieo_regex("(jie|jio) (a|b), ((?:\\+|-)\\d+)");
  smatch matches;

  ifstream infile(argv[1]);
  for (string line; getline(infile, line);) {
    if (regex_match(line, matches, register_regex)) {
      if (matches[1] == "hlf") {
        machine.add_instruction(Hlf{string_to_register(matches[2])});
      } else if (matches[1] == "tpl") {
        machine.add_instruction(Tpl{string_to_register(matches[2])});
      } else if (matches[1] == "inc") {
        machine.add_instruction(Inc{string_to_register(matches[2])});
      } else {
        cout << "? " << matches[1] << endl;
      }
    } else if (regex_match(line, matches, jmp_regex)) {
      int the_jump = stoi(matches[1]);
      machine.add_instruction(Jmp{the_jump});
    } else if (regex_match(line, matches, jieo_regex)) {
      if (matches[1] == "jie") {
        machine.add_instruction(
            {Jie{string_to_register(matches[2]), stoi(matches[3])}});
      } else if (matches[1] == "jio") {
        machine.add_instruction(
            {Jio{string_to_register(matches[2]), stoi(matches[3])}});
      } else {
        cout << "? " << matches[1] << endl;
      }
    } else {
      cout << "?? " << line << endl;
    }
  }
  // for (auto i : machine.instructions) {
  //   machine.print_instruction(i);
  // }

  machine.run();
  machine.print();

  return 0;
}
