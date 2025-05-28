#include <iostream>
#include <vector>

using namespace std;

int main() {

  int64_t target{200};
  vector<int64_t> coins{1, 2, 5, 10, 20, 50, 100, 200};

  vector<size_t> ways(target + 1, 0);
  ways.at(0) = 1;

  for (auto it = coins.begin(); it != coins.end(); ++it) {
    for (int64_t i = *it; i < ways.size(); ++i) {
      ways.at(i) = ways.at(i) + ways.at(i - *it);
    }
  }

  std::cout << ways.at(target) << "\n";
}
