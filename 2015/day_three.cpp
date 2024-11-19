#include <fstream>
#include <iostream>
#include <map>
#include <ostream>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

typedef tuple<int, int> location;

struct location_comp {
  bool operator()(const location &lhs, const location &rhs) {
    if (std::get<0>(lhs) == std::get<0>(rhs)) {
      return std::get<1>(lhs) > std::get<1>(rhs);
    } else {
      return std::get<0>(lhs) > std::get<0>(rhs);
    }
  }
};

string location_string(location l) {
  stringstream stream = {};
  stream << "(" << get<0>(l) << ", " << get<1>(l) << ")";
  return stream.str();
}

void tracker(string the_string) {
  map<location, int> house_visits = {};
  location spot = make_tuple(0, 0);
  auto [index, inserted] = house_visits.try_emplace(spot, 1);
  bool position_update = true;

  for (char c : the_string) {
    position_update = true;
    if (c == '<') {
      get<0>(spot) -= 1;
    } else if (c == '>') {
      get<0>(spot) += 1;
    } else if (c == '^') {
      get<1>(spot) += 1;
    } else if (c == 'v') {
      get<1>(spot) -= 1;
    } else {
      position_update = false;
    }

    if (position_update) {
      auto [index, inserted] = house_visits.try_emplace(spot, 1);
      if (!inserted) {
        index->second = index->second + 1;
      }
    }
  }

  cout << "solo visits: " << house_visits.size() << endl;
}

void pair_tracker(string the_string) {
  map<location, int> house_visits = {};
  int total_visits = 0;
  location santa_spot = make_tuple(0, 0);
  location robo_santa_spot = make_tuple(0, 0);
  auto [index, inserted] = house_visits.try_emplace(santa_spot, 1);
  if (!inserted) {
    index->second = index->second + 1;
  }
  auto [index_r, inserted_r] = house_visits.try_emplace(robo_santa_spot, 1);
  if (!inserted_r) {
    index_r->second = index_r->second + 1;
  };
  bool position_update = true;

  for (char c : the_string) {
    position_update = true;
    if (c == '<') {
      if (total_visits % 2 == 0) {
        get<0>(santa_spot) -= 1;
      } else {
        get<0>(robo_santa_spot) -= 1;
      }
    } else if (c == '>') {
      if (total_visits % 2 == 0) {
        get<0>(santa_spot) += 1;
      } else {
        get<0>(robo_santa_spot) += 1;
      }
    } else if (c == '^') {
      if (total_visits % 2 == 0) {
        get<1>(santa_spot) += 1;
      } else {
        get<1>(robo_santa_spot) += 1;
      }
    } else if (c == 'v') {
      if (total_visits % 2 == 0) {
        get<1>(santa_spot) -= 1;
      } else {
        get<1>(robo_santa_spot) -= 1;
      }
    } else {
      position_update = false;
    }

    if (position_update) {
      if (total_visits % 2 == 0) {
        auto [index, inserted] = house_visits.try_emplace(santa_spot, 1);
        if (!inserted) {
          index->second = index->second + 1;
        }
      } else {
        auto [index, inserted] = house_visits.try_emplace(robo_santa_spot, 1);
        if (!inserted) {
          index->second = index->second + 1;
        }
      }
      total_visits += 1;
      // cout <<  "s: " << location_string(santa_spot) << endl;
    }
  }

  cout << "pair visits: " << house_visits.size() << endl;
}

int main() {
  vector<string> paths = {">", "^>v<", "^v^v^v^v^v"};

  for (auto path : paths) {
    tracker(path);
    pair_tracker(path);
  }

  std::ifstream ifs("day_three_visits.txt");
  std::string line((std::istreambuf_iterator<char>(ifs)),
                   (std::istreambuf_iterator<char>()));
  tracker(line);
  pair_tracker(line);

  return 0;
}
