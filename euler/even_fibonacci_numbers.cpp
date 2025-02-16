#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char **argv) {

  int a{1};
  int b{2};

  int swap{0};

  int limit{stoi(argv[1])};

  int even_sum{2};

  while (true) {
    swap = b;
    b = a + b;
    a = swap;

    if (b >= limit) {
      break;
    }

    if (b % 2 == 0) {
      even_sum += b;
    }

    cout << b << " ";
  }

  cout << endl;

  cout << even_sum << endl;

  return 0;
};
