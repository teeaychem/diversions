#include <iostream>
#include <string>
using namespace std;

int main(int argc, char **argv) {

  int n = stoi(argv[1]);

  int smallest = 1;

  bool evenly_divisible = false;

  while (true) {

    evenly_divisible = true;

    for (int i = 1; i <= n; i++) {
      if (smallest % i != 0) {
        evenly_divisible = false;
        break;
      }
    }

    if (evenly_divisible) {
      cout << smallest << endl;
      break;
    }

    smallest++;
  }

  return 0;
}
