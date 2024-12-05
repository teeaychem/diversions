#include <algorithm>
#include <fstream>
#include <iostream>
#include <queue>
#include <regex>
#include <unordered_map>
#include <vector>
using namespace std;

struct recepient {
  enum { BOT, OUTPUT } tag;
  union {
    int bot;
    int output;
  };
};

class bot {
public:
  int number;
  vector<int> input{};
  recepient low;
  recepient high;
};

unordered_map<int, int> output_map;
unordered_map<int, bot> bot_map;
queue<int> check_stack{};

void update(int bot_idx) {
  bot &the_bot = bot_map.at(bot_idx);
  if (the_bot.input.size() == 2) {
    cout << "bot " << the_bot.number << " acts" << endl;
    sort(the_bot.input.begin(), the_bot.input.end(), less<int>());
    cout << "inputs are: " << the_bot.input[0] << " " << the_bot.input[1]
         << endl;
    // if (the_bot.input[0] == 17 && the_bot.input[1] == 61) {
    //   cout << ">_> " << the_bot.number << endl;
    //   exit(1);
    // }

    switch (the_bot.low.tag) {
    case recepient::BOT:
      bot_map.at(the_bot.low.bot).input.push_back(the_bot.input[0]);
      check_stack.push(the_bot.low.bot);
      break;
    case recepient::OUTPUT:
      output_map[the_bot.low.output] = the_bot.input[0];
      break;
    }

    switch (the_bot.high.tag) {
    case recepient::BOT:
      bot_map.at(the_bot.high.bot).input.push_back(the_bot.input[1]);
      check_stack.push(the_bot.high.bot);
      break;
    case recepient::OUTPUT:
      output_map[the_bot.high.output] = the_bot.input[1];
      break;
    }

    the_bot.input.clear();
  }
}

int main(int argc, char **argv) {

  // bot zero = bot{.number = 0,
  //                .low = recepient{recepient::OUTPUT, {2}},
  //                .high = recepient{recepient::OUTPUT, {0}}};

  // bot one = bot{.number = 1,
  //               .low = recepient{recepient::OUTPUT, {1}},
  //               .high = recepient{recepient::BOT, {0}}};

  // bot two = bot{.number = 2,
  //               .low = recepient{recepient::BOT, {1}},
  //               .high = recepient{recepient::BOT, {0}}};

  // bot_map[0] = zero;
  // bot_map[1] = one;
  // bot_map[2] = two;
  // bot_map.at(2).input.push_back(5);
  // check_stack.push(2);
  // bot_map.at(1).input.push_back(3);
  // check_stack.push(1);
  // bot_map.at(2).input.push_back(2);
  // check_stack.push(2);

  regex bot_regex("bot (\\d+) gives low to (output|bot) (\\d+) and high to "
                  "(output|bot) (\\d+)");
  regex value_regex("value (\\d+) goes to bot (\\d+)");

  smatch rm;
  ifstream infile(argv[1]);
  for (string line; getline(infile, line);) {
    if (regex_match(line, rm, bot_regex)) {
      cout << "bot: " << rm[0] << endl;
      bot new_bot = bot{};
      new_bot.number = stoi(rm[1]);
      if (rm[2] == "bot") {
        new_bot.low = recepient{recepient::BOT, {stoi(rm[3])}};
      } else if (rm[2] == "output") {
        new_bot.low = recepient{recepient::OUTPUT, {stoi(rm[3])}};
      } else {
        cout << "? " << rm[2] << endl;
        exit(1);
      }

      if (rm[4] == "bot") {
        new_bot.high = recepient{recepient::BOT, {stoi(rm[5])}};
      } else {
        new_bot.high = recepient{recepient::OUTPUT, {stoi(rm[5])}};
      }

      bot_map[new_bot.number] = new_bot;
    }
  }
  infile.clear();
  infile.seekg(0, ios::beg);
  for (string line; getline(infile, line);) {
    if (regex_match(line, rm, value_regex)) {
      cout << "value: " << rm[0] << endl;
      bot_map.at(stoi(rm[2])).input.push_back(stoi(rm[1]));
      check_stack.push(stoi(rm[2]));
    }
  }

  while (!check_stack.empty()) {
    update(check_stack.front());
    check_stack.pop();
  }
  for (auto p : output_map) {
    cout << p.first << " " << p.second << endl;
  }
  cout << "x: " << output_map[0] * output_map[1] * output_map[2] << endl;

  return 0;
}
