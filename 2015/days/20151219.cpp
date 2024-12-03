#include <algorithm>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <iterator>
#include <regex>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

vector<string> split_molecules(string s) {
  vector<string> the_molecules{};
  string buffer{};
  buffer.push_back(s[0]);
  for (size_t i = 1; i < s.size(); i++) {
    char the_char = s[i];

    if (('A' <= the_char && the_char <= 'Z') || the_char == 'e') {
      string molecule{};
      copy(buffer.begin(), buffer.end(), back_insert_iterator(molecule));
      the_molecules.push_back(molecule);
      buffer.clear();
    }
    buffer.push_back(the_char);
  }
  the_molecules.push_back(buffer);
  return the_molecules;
}

void test_run() {
  unordered_set<string> generation_set{};
  unordered_map<string, vector<string>> replacements{};
  vector<string> h = {"HO", "OH"};
  vector<string> o = {"HH"};
  replacements["H"] = h;
  replacements["O"] = o;

  string the_string = "HOHOHO";
  vector<string> seen_molecules{};
  auto test_molecules = split_molecules(the_string);
  for (size_t i = 0; i < test_molecules.size(); i++) {
    string m = test_molecules[i];
    if (replacements.contains(m)) {
      for (size_t j = 0; j < replacements[m].size(); j++) {

        string m_string{};
        for (auto seen_m : seen_molecules) {
          m_string += seen_m;
        }
        m_string += replacements[m][j];
        for (size_t k = i + 1; k < test_molecules.size(); k++) {
          m_string += test_molecules[k];
        }

        generation_set.insert(m_string);
      }
    }
    seen_molecules.push_back(m);
  }

  for (auto g : generation_set) {
    cout << g << endl;
  }
}

int counter(unordered_map<string, vector<string>> &replacements,
            string &the_sequence) {
  unordered_set<string> generation_set{};

  vector<string> seen_molecules{};
  auto split_sequence = split_molecules(the_sequence);

  for (size_t i = 0; i < split_sequence.size(); i++) {
    string m = split_sequence[i];
    if (replacements.contains(m)) {
      for (size_t j = 0; j < replacements[m].size(); j++) {

        string m_string{};
        for (auto seen_m : seen_molecules) {
          m_string += seen_m;
        }
        m_string += replacements[m][j];
        for (size_t k = i + 1; k < split_sequence.size(); k++) {
          m_string += split_sequence[k];
        }

        generation_set.insert(m_string);
      }
    }
    seen_molecules.push_back(m);
  }

  return generation_set.size();
}

unordered_set<string>
unreplace(unordered_map<string, vector<string>> &unreplacements, string s) {

  unordered_set<string> replacements{};
  for (auto kv : unreplacements) {
    auto p = s.find(kv.first);
    if (p != string::npos) {
      for (auto redu : kv.second) {
        string replace = s;
        replace.replace(p, kv.first.size(), redu);

        // cout << k << endl;
        // cout << "s: " << s << " k: " << kv.first << " r: " << redu << endl;
        // cout << "p: " << p << " l: " << kv.first.size() << " r: " << replace
        //      << endl;

        // cout << replace << endl;
        replacements.insert(replace);
      }
    }
  }
  return replacements;
}

void guess(unordered_map<string, vector<string>> &unreplacements, string s,
           int k) {
  if (s == "e") {
    cout << "guess: " << k << endl;
    exit(0);
  } else {
    vector<string> options{};
    for (auto kv : unreplacements) {
      auto p = s.find(kv.first);
      if (p != string::npos) {
        string o = kv.first;
        options.push_back(o);
      }
    }
    sort(options.begin(), options.end(),
         [](const string &a, const string &b) { return a.size() > b.size(); });
    for (auto opt : options) {
      for (auto r : unreplacements[opt]) {
        auto p = s.find(opt);
        string replaced = s;
        replaced.replace(p, opt.size(), r);
        guess(unreplacements, replaced, k + 1);
      }
    }
  }
}

int main(int argc, char **argv) {

  // test_run();

  if (argc != 3) {
    cout << "A map and sequence is needed for anything else…" << endl;
    exit(0);
  }

  unordered_map<string, vector<string>> replacements{};
  unordered_map<string, vector<string>> unreplacements{};

  ifstream in_map(argv[1]);
  ifstream in_sequence(argv[2]);

  regex cmd_regex("([A-Za-z]+) => ([A-Za-z]+)");
  smatch matches;

  for (string line; getline(in_map, line);) {
    if (regex_search(line, matches, cmd_regex)) {
      if (!replacements.contains(matches[1])) {
        replacements[matches[1]] = {};
      }
      replacements[matches[1]].push_back(matches[2]);

      if (!unreplacements.contains(matches[2])) {
        unreplacements[matches[2]] = {};
      }
      unreplacements[matches[2]].push_back(matches[1]);
    }
  }

  string the_sequence = {};
  getline(in_sequence, the_sequence);

  cout << counter(replacements, the_sequence) << endl;

  guess(unreplacements, the_sequence, 0);

  // for (auto e : unreplacements) {
  //   cout << e.first << " ";
  //   for (auto y : e.second) {
  //     cout << y << " ";
  //   }
  //   cout << endl;
  // }

  // the_sequence = "ORnFArPMg";

  // int counter = 0;
  // unordered_set<string> more_replacements = {the_sequence};

  // while (!more_replacements.contains("e")) {
  //   // cout << counter << endl;
  //   counter += 1;
  //   unordered_set<string> update{};
  //   for (auto partial_replacement : more_replacements) {
  //     auto further_replacements =
  //         unreplace(unreplacements, partial_replacement);
  //     for (auto further : further_replacements) {
  //       // cout << further << endl;
  //       update.insert(further);
  //     }
  //   }

  //   more_replacements = update;
  //   if (counter % 2 == 0) {
  //     cout << counter << endl;
  //   }
  // }
  // cout << counter << endl;

  return 0;
}
