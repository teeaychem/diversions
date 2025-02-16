#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char **argv) {

  int limit = stoi(argv[1]);
  int sum = 0;

  for (int i = 1; i < limit; i++) {
    if (i % 3 == 0 || i % 5 == 0) {
      sum += i;
    }
  }
  cout << sum << endl;

  return 0;
}
