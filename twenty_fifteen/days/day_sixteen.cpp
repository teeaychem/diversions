#include <fstream>

#include <iostream>
#include <optional>
#include <regex>
#include <sys/types.h>
#include <vector>

using namespace std;

class sue {
public:
  optional<int> number;
  optional<int> children;
  optional<int> cats;
  optional<int> samoyeds;
  optional<int> pomeranians;
  optional<int> akitas;
  optional<int> vizslas;
  optional<int> goldfish;
  optional<int> trees;
  optional<int> cars;
  optional<int> perfumes;
};

bool known_match(sue &a, sue &b) {
  if (a.children.has_value() && b.children.has_value()) {
    if (a.children.value() != b.children.value()) {
      return false;
    }
  }
  if (a.cats.has_value() && b.cats.has_value()) {
    if (a.cats.value() != b.cats.value()) {
      return false;
    }
  }
  if (a.samoyeds.has_value() && b.samoyeds.has_value()) {
    if (a.samoyeds.value() != b.samoyeds.value()) {
      return false;
    }
  }
  if (a.pomeranians.has_value() && b.pomeranians.has_value()) {
    if (a.pomeranians.value() != b.pomeranians.value()) {
      return false;
    }
  }
  if (a.akitas.has_value() && b.akitas.has_value()) {
    if (a.akitas.value() != b.akitas.value()) {
      return false;
    }
  }
  if (a.vizslas.has_value() && b.vizslas.has_value()) {
    if (a.vizslas.value() != b.vizslas.value()) {
      return false;
    }
  }
  if (a.goldfish.has_value() && b.goldfish.has_value()) {
    if (a.goldfish.value() != b.goldfish.value()) {
      return false;
    }
  }
  if (a.trees.has_value() && b.trees.has_value()) {
    if (a.trees.value() != b.trees.value()) {
      return false;
    }
  }
  if (a.cars.has_value() && b.cars.has_value()) {
    if (a.cars.value() != b.cars.value()) {
      return false;
    }
  }
  if (a.perfumes.has_value() && b.perfumes.has_value()) {
    if (a.perfumes.value() != b.perfumes.value()) {
      return false;
    }
  }
  return true;
}

bool known_match_two(sue &a, sue &b) {

  if (a.cats.has_value() && b.cats.has_value()) {
    if (a.cats.value() >= b.cats.value()) {
      return false;
    }
  }
  if (a.trees.has_value() && b.trees.has_value()) {
    if (a.trees.value() >= b.trees.value()) {
      return false;
    }
  }

  if (a.pomeranians.has_value() && b.pomeranians.has_value()) {
    if (a.pomeranians.value() <= b.pomeranians.value()) {
      return false;
    }
  }
  if (a.goldfish.has_value() && b.goldfish.has_value()) {
    if (a.goldfish.value() <= b.goldfish.value()) {
      return false;
    }
  }

  if (a.children.has_value() && b.children.has_value()) {
    if (a.children.value() != b.children.value()) {
      return false;
    }
  }

  if (a.samoyeds.has_value() && b.samoyeds.has_value()) {
    if (a.samoyeds.value() != b.samoyeds.value()) {
      return false;
    }
  }

  if (a.akitas.has_value() && b.akitas.has_value()) {
    if (a.akitas.value() != b.akitas.value()) {
      return false;
    }
  }
  if (a.vizslas.has_value() && b.vizslas.has_value()) {
    if (a.vizslas.value() != b.vizslas.value()) {
      return false;
    }
  }

  if (a.cars.has_value() && b.cars.has_value()) {
    if (a.cars.value() != b.cars.value()) {
      return false;
    }
  }
  if (a.perfumes.has_value() && b.perfumes.has_value()) {
    if (a.perfumes.value() != b.perfumes.value()) {
      return false;
    }
  }
  return true;
}

int main(int argc, char **argv) {

  if (argc != 2) {
    cout << "A file is needed for anything else…" << endl;
    exit(0);
  }

  vector<sue> sues{};

  regex regex_number("Sue (\\d+)");
  regex regex_children("children: (\\d+)");
  regex regex_cats("cats: (\\d+)");
  regex regex_samoyeds("samoyeds: (\\d+)");
  regex regex_pomeranians("pomeranians: (\\d+)");
  regex regex_akitas("akitas: (\\d+)");
  regex regex_vizslas("vizslas: (\\d+)");
  regex regex_goldfish("goldfish: (\\d+)");
  regex regex_trees("trees: (\\d+)");
  regex regex_cars("cars: (\\d+)");
  regex regex_perfumes("perfumes: (\\d+)");
  smatch matches;

  string file = argv[1];
  ifstream infile(file);
  cout << "Reading: " << file << endl;
  for (string line; getline(infile, line);) {
    regex_search(line, matches, regex_number);
    sue new_sue = sue{
        .number = (regex_search(line, matches, regex_number)
                       ? optional(stoi(matches[1]))
                       : nullopt),
        .children = (regex_search(line, matches, regex_children)
                         ? optional(stoi(matches[1]))
                         : nullopt),
        .cats = (regex_search(line, matches, regex_cats)
                     ? optional(stoi(matches[1]))
                     : nullopt),
        .samoyeds = (regex_search(line, matches, regex_samoyeds)
                         ? optional(stoi(matches[1]))
                         : nullopt),
        .pomeranians = (regex_search(line, matches, regex_pomeranians)
                            ? optional(stoi(matches[1]))
                            : nullopt),
        .akitas = (regex_search(line, matches, regex_akitas)
                       ? optional(stoi(matches[1]))
                       : nullopt),
        .vizslas = (regex_search(line, matches, regex_vizslas)
                        ? optional(stoi(matches[1]))
                        : nullopt),
        .goldfish = (regex_search(line, matches, regex_goldfish)
                         ? optional(stoi(matches[1]))
                         : nullopt),
        .trees = (regex_search(line, matches, regex_trees)
                      ? optional(stoi(matches[1]))
                      : nullopt),
        .cars = (regex_search(line, matches, regex_cars)
                     ? optional(stoi(matches[1]))
                     : nullopt),
        .perfumes = (regex_search(line, matches, regex_perfumes)
                         ? optional(stoi(matches[1]))
                         : nullopt),
    };
    sues.push_back(new_sue);
  }

  sue big_sue = sue{.number = nullopt,
                    .children = optional(3),
                    .cats = optional(7),
                    .samoyeds = optional(2),
                    .pomeranians = optional(3),
                    .akitas = optional(0),
                    .vizslas = optional(0),
                    .goldfish = optional(5),
                    .trees = optional(3),
                    .cars = optional(2),
                    .perfumes = optional(1)};

  for (auto s : sues) {
    if (known_match(big_sue, s)) {
      cout << s.number.value() << endl;
    }
    if (known_match_two(big_sue, s)) {
      cout << s.number.value() << endl;
    }
  }

  return 0;
}
