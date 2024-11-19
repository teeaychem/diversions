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
      cout << "Unexpected: " << c << " ." << endl;
      position_update = false;
    }

    if (position_update) {
      auto [index, inserted] = house_visits.try_emplace(spot, 1);
      if (!inserted) {
        index->second = index->second + 1;
      }
    }
  }

  auto a = house_visits.find(make_tuple(0, 0))->second;
  cout << "x " << a << endl;
  cout << "t: " << house_visits.size() << endl;
}

int main() {
  vector<string> paths = {">", "^>v<", "^v^v^v^v^v"};

  for (auto path : paths) {
    tracker(path);
  }

  std::ifstream ifs("day_three_visits.txt");
  std::string line((std::istreambuf_iterator<char>(ifs)),
                   (std::istreambuf_iterator<char>()));
  tracker(line);

  return 0;
}
