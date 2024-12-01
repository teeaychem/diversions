
#include <iostream>
#include <vector>

typedef unsigned long int code_t;

using namespace std;
code_t CODE = 20151125;

int ctoi(size_t x, size_t y) {
  size_t i = 0;
  size_t j = 0;
  int n = 0;
  while (true) {
    if (j == x && i == y) {
      return n;
    }
    if (j == 0) {
      j = i + 1;
      i = 0;
    } else {
      i = i + 1;
      j = j - 1;
    }
    n += 1;
  }
}

code_t code_at(int x, int y) {
  code_t code = CODE;
  int l = ctoi(x, y);
  for (int i = 0; i < l; i++) {
    code = (code * 252533) % 33554393;
  }
  return code;
}

void grid(size_t s) {
  code_t code = CODE;
  vector<vector<int>> g = vector(s, vector(s, 0));

  size_t x = 0;
  size_t y = 0;
  for (size_t v = 0; v < s * s; v++) {
    if (x == s || y == s) {
      break;
    }
    g[y][x] = code;
    code = (code * 252533) % 33554393;
    if (y == 0) {
      y = min(x + 1, s);
      x = 0;
    } else {
      x = min(x + 1, s);
      y = max(y - 1, (size_t)0);
    }
  }

  for (size_t y = 0; y < s; y++) {
    for (size_t x = 0; x < s; x++) {
      cout << format("{:10}", g[y][x]) << " ";
    }
    cout << endl;
  }
}

int main(int argc, char **argv) {
  grid(12);

  int x = 5;
  int y = 5;
  code_t code = code_at(x - 1, y - 1);
  cout << "code at (" << x << ", " << y << ") is " << code << endl;

  return 0;
}
