#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char **argv) {

  ifstream infile(argv[1]);
  for (string line; getline(infile, line);) {
    int sum{0};

    // int offset = 1;
    int offset = line.size() / 2;

    for (size_t i = 0; i < line.size(); i++) {
      if (line[i] == line[(i + offset) % line.size()]) {
        sum += line[i] - '0';
      }
    }

    cout << sum << endl;
  }

  return 0;
}
