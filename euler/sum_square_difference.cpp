#include <iostream>
#include <string>
using namespace std;

int main(int argc, char **argv) {

  int64_t n = stoi(argv[1]);

  int64_t sum = (n * (n + 1)) / 2;
  int64_t sum_square = pow(sum, 2);

  int64_t square_sum = 0;
  for (int i = 1; i <= n; i++) {
    square_sum += pow(i, 2);
  }

  cout << sum_square - square_sum << endl;

  return 0;
}
