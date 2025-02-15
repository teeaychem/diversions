#include <cctype>
#include <fstream>
#include <iostream>
#include <iterator>
#include <optional>
#include <string>
#include <vector>
using namespace std;

string decompress(string in, bool vee_two) {
  string inner_d;
  string decompressed{};
  string d_buffer = {};
  optional<int> d_buffer_awaiting = nullopt;
  optional<int> d_buffer_multi = nullopt;
  string i_buffer{};
  int eye;

  size_t i = 0;
  while (i < in.size()) {
    if (d_buffer_awaiting.has_value()) {
      d_buffer.push_back(in[i]);
      i++;
      d_buffer_awaiting.value() -= 1;
      if (d_buffer_awaiting.value() == 0) {
        d_buffer_awaiting = nullopt;
        inner_d = d_buffer;
        d_buffer.clear();
        if (vee_two) {
          size_t last_size;
          while (true) {
            last_size = inner_d.size();
            inner_d = decompress(inner_d, true);
            if (last_size == inner_d.size()) {
              break;
            }
          }
        }

        for (int j = 0; j < d_buffer_multi.value(); j++) {
          for (auto bc : inner_d) {
            decompressed.push_back(bc);
          }
        }

        d_buffer_multi = nullopt;
      }
    } else {
      if (in[i] == '(') {
        i++;
        while (i < in.size() && isdigit(in[i])) {
          i_buffer.push_back(in[i]);
          i++;
        }
        eye = stoi(i_buffer);
        d_buffer_awaiting = eye;
        i_buffer.clear();
        if (in[i] != 'x') {
          cout << "x_x" << endl;
        }
        i++;
        while (i < in.size() && isdigit(in[i])) {
          i_buffer.push_back(in[i]);
          i++;
        }
        eye = stoi(i_buffer);
        d_buffer_multi = eye;
        i_buffer.clear();
        if (in[i] != ')') {
          cout << "x_x" << endl;
        }
        i++;
      } else {
        decompressed.push_back(in[i]);
        i++;
      }
    }
  }
  return decompressed;
}

int main(int argc, char **argv) {
  string decompressed;

  vector<string> tests = {"ADVENT",      "A(1x5)BC",
                          "(3x3)XYZ",    "A(2x2)BCD(2x2)EFG",
                          "(6x1)(1x3)A", "X(8x2)(3x3)ABCY"};

  for (auto t : tests) {
    decompressed = decompress(t, true);
    cout << decompressed << endl;
    cout << "size: " << decompressed.size() << endl;
  }

  ifstream infile(argv[1]);
  string all_instructions{};
  for (string line; getline(infile, line);) {
    decompressed = decompress(line, true);
    cout << decompressed << endl;
    cout << "size: " << decompressed.size() << endl;
  }

  return 0;
}
