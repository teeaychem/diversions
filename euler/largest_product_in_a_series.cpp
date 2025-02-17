#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char **argv) {

  int64_t subsequence_length = stoi(argv[1]);

  // Given as a text file of contiguous digits on a single line.
  vector<int64_t> sequence{};

  ifstream infile(argv[2]);
  for (string line; getline(infile, line);) {
    for (size_t i = 0; i < line.size(); i++) {
      sequence.push_back(line[i] - '0');
    }
  }

  // The 'head' is the index of the digit following the current subsequence,
  // rather than the largest index of the subsequence.
  int64_t head = 0;
  int64_t non_zero_count = 0;

  // Search for the head of an intial sub-sequence with all non-zero digits.
  for (; head < sequence.size(); head++) {
    if (non_zero_count == subsequence_length) {
      break;
    } else if (sequence[head] == 0) {
      non_zero_count = 0;
    } else {
      non_zero_count++;
    }
  }

  // Infer the tail of the subsequence from the head
  int64_t tail = head - subsequence_length;

  // A rolling product…
  int64_t product = 1;

  // …set to the initial subsequence.
  for (int64_t i = tail; i < head; i++) {
    product *= sequence[i];
  }

  int64_t max_product = product;
  int64_t skip_count = 0;

  while (head <= sequence.size()) {
    // Remove the tail from the subsequence.
    if (sequence[tail] != 0) {
      product /= sequence[tail];
    }

    // Either…
    if (sequence[head] == 0) {
      // The head is zero, skipped, and every product is ignored as a candidate
      // until the tail has passed over the digit.
      skip_count = subsequence_length + 1;
    } else {
      // The head is non-zero…
      product *= sequence[head];
      // … and if there is no zero in the subsequence, a new largest product may
      // have been found.
      if (skip_count == 0 && max_product < product) {
        max_product = product;
      }
    }

    // Move to the next subsequence
    tail++;
    head++;

    skip_count = max((int64_t)0, --skip_count);
  }

  cout << max_product << endl;

  return 0;
}
