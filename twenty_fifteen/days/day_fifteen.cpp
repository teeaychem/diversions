#include <algorithm>
#include <cstddef>
#include <fstream>
#include <functional>
#include <iostream>
#include <regex>
#include <vector>
using namespace std;

void vec_printer(vector<uint> &v) {
  for (auto e : v) {
    cout << e << " ";
  }
  cout << endl;
};

struct ingredient {
  string name;
  int capacity;
  int durability;
  int flavour;
  int texture;
  int calories;

  void print() {
    cout << this->name << endl;
    cout << this->capacity << endl;
    cout << this->durability << endl;
    cout << this->flavour << endl;
    cout << this->texture << endl;
    cout << this->calories << endl;
  }
};

// stars and bars approach, with help on the write up on gray codes from:
// https://stackoverflow.com/questions/127704/algorithm-to-return-all-combinations-of-k-elements-from-n/42190945#42190945

void subsets_helper(function<void(vector<uint> &)> f, uint n, uint k,
                    vector<uint> &v, uint s, uint j) {
  if (j == k) {
    f(v);
  } else {
    for (uint i = s; i < n; i++) {
      v.push_back(i);
      subsets_helper(f, n, k, v, i + 1, j + 1);
      v.pop_back();
    }
  }
}

void apply_to_k_subsets(uint n, uint k, function<void(vector<uint> &)> f) {
  vector<uint> x{};
  subsets_helper(f, n, k, x, 0, 0);
}

function<void(vector<uint> &)> go_between(uint total, uint groups,
                                          function<void(vector<uint> &)> g) {
  auto transform_to_distribution = [total, groups, g](vector<uint> &v) {
    vector<uint> dist_vec{};
    uint taken = 0;
    for (uint z = 0; z < groups - 1; z++) {
      dist_vec.push_back(v[z] - z - taken);
      taken += (v[z] - z) - taken;
    }
    dist_vec.push_back(total + (groups - 1) - (groups - 1) - taken);
    g(dist_vec);
  };
  return transform_to_distribution;
}

void apply_to_k_splits_of_n(uint n, uint k, function<void(vector<uint> &)> f) {
  apply_to_k_subsets(n + (k - 1), k - 1, go_between(n, k, f));
}

int main(int argc, char **argv) {

  if (argc != 2) {
    cout << "A file is needed for anything else…" << endl;
    exit(0);
  }

  vector<ingredient> ingredients;

  string the_file = argv[1];

  ifstream infile(the_file);

  string line;
  regex cmd_regex("([A-Z][a-z]+): "
                  "capacity (-?\\d+), "
                  "durability (-?\\d+), "
                  "flavor (-?\\d+), "
                  "texture (-?\\d+), "
                  "calories (-?\\d+)");
  smatch matches;

  for (string line; getline(infile, line);) {
    if (regex_search(line, matches, cmd_regex)) {

      ingredient ingredient = {.name = matches[1],
                               .capacity = static_cast<int>(stoi(matches[2])),
                               .durability = static_cast<int>(stoi(matches[3])),
                               .flavour = static_cast<int>(stoi(matches[4])),
                               .texture = static_cast<int>(stoi(matches[5])),
                               .calories = static_cast<int>(stoi(matches[6]))

      };
      ingredients.push_back(ingredient);

    } else {
      cout << "x_x" << endl;
      exit(1);
    }
  }

  cout << ingredients.size() << endl;
  for (auto i : ingredients) {
    i.print();
  }

  int best_total{0};

  auto do_it = [&best_total, ingredients](vector<uint> &mix) {
    // vec_printer(mix);
    int total_capacity{0};
    int total_durability{0};
    int total_flavour{0};
    int total_texture{0};
    int total_calories{0};
    for (size_t j = 0; j < ingredients.size(); j++) {
      total_capacity += mix[j] * ingredients[j].capacity;
      total_durability += mix[j] * ingredients[j].durability;
      total_flavour += mix[j] * ingredients[j].flavour;
      total_texture += mix[j] * ingredients[j].texture;
      total_calories += mix[j] * ingredients[j].calories;
    }
    int total = max(0, total_capacity) * max(0, total_durability) *
                max(0, total_flavour) * max(0, total_texture);
    total = max(total, 0);
    if (total > best_total && total_calories == 500) {
      best_total = total;
    }
  };

  apply_to_k_splits_of_n(100, ingredients.size(), do_it);

  cout << best_total << endl;

  return 0;
}
