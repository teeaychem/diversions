#include <iostream>
#include <vector>
using namespace std;

vector<int> next(vector<int> current) {
  vector<int> to_return;
  if (current.empty()) {
    to_return.push_back(0);
  } else {
    int following = current[0];
    int following_count = 1;
    for (size_t i = 1; i < current.size(); i++) {
      if (current[i] == following) {
        following_count += 1;
      } else {
        to_return.push_back(following_count);
        to_return.push_back(following);
        following = current[i];
        following_count = 1;
      }
    }
    to_return.push_back(following_count);
    to_return.push_back(following);
  }

  return to_return;
}

void show_sequence(vector<int> sequence) {
  for (int s : sequence) {
    cout << s;
  }
  cout << endl;
}

int main() {
  vector<int> sequence = {1, 2, 1};
  for (size_t i = 0; i < 50; i++) {
    sequence = next(sequence);
  }
  cout << sequence.size() << endl;

  return 0;
}
