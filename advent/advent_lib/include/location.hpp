#pragma once

#include <format>
#include <string>
#include <utility>
namespace advent {
namespace location {
using namespace std;

typedef pair<int, int> coordinate;
enum direction {
  up,
  down,
  left,
  right,
};

inline direction rotate_left(direction d) {
  switch (d) {
  case direction::up:
    return direction::left;
  case direction::down:
    return direction::right;
  case direction::left:
    return direction::down;
  case direction::right:
    return direction::up;
  default:
    exit(1);
  }
}

inline string direction_string(direction &d) {
  string the_string;
  switch (d) {
  case direction::up:
    the_string = "up";
    break;
  case direction::down:
    the_string = "down";
    break;
  case direction::left:
    the_string = "left";
    break;
  case direction::right:
    the_string = "right";
    break;
  }
  return the_string;
}

inline direction rotate_right(direction d) {
  switch (d) {
  case direction::up:
    return direction::right;
  case direction::down:
    return direction::left;
  case direction::left:
    return direction::up;
  case direction::right:
    return direction::down;
  default:
    exit(1);
  }
}

inline coordinate maps_to(coordinate &c, const direction &d) {
  coordinate new_c = c;
  switch (d) {
  case direction::up:
    new_c.second -= 1;
    break;
  case direction::down:
    new_c.second += 1;
    break;
  case direction::left:
    new_c.first -= 1;
    break;
  case direction::right:
    new_c.first += 1;
    break;
  default:
    exit(1);
  }
  return new_c;
}

inline bool within_grid(coordinate &c, const coordinate &tl, const coordinate &br) {
  return (tl.first <= c.first && c.first <= br.first) && (tl.second <= c.second && c.second <= br.second);
}

inline string location_string(coordinate l) {
  return format("({},{})", l.first, l.second);
}

} // namespace location
} // namespace advent
