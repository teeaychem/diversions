
#include <climits>
#include <iostream>
#include <vector>

using namespace std;

int next_presence(vector<int> &v, int i) {
  int ptr = i;
  for (size_t j = 1; j <= v.size(); j++) {
    ptr = (i + j) % v.size();
    if (v[ptr] != 0) {
      break;
    }
  }
  return ptr;
}

bool take(vector<int> &v, int i) {
  int next = next_presence(v, i);
  if (i == next) {
    return false;
  } else {
    v[i] += v[next];
    v[next] = 0;
    return true;
  }
}

void pv(vector<int> &v) {
  for (auto x : v) {
    cout << x << " ";
  }
  cout << endl;
}

void part_one() {
  vector<int> circle = vector(5, 1);

  int next = 0;
  while (take(circle, next)) {
    next = next_presence(circle, next);
  }
  cout << next_presence(circle, 0) + 1 << endl;
}

int main(int argc, char **argv) {

  vector<int> circle{};
  for (int i = 1; i <= 5; i++) { //
    circle.push_back(i);
  }
  size_t i = 0;
  while (circle.size() != 1) {
    size_t opposite = (i + (circle.size() / 2)) % circle.size();
    if ((i % circle.size()) < opposite) {
      i = i + 1;
    }
    circle.erase(circle.begin() + opposite);
    if (i == circle.size()) {
      i = 0;
    }
  }
  pv(circle);

  return 0;
}
