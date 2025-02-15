
#include <iostream>
#include <vector>

using namespace std;

void add_row(vector<string> &rows) {
  size_t last_row = rows.size() - 1;
  int row_length = rows[last_row].size();
  string new_row = "";
  for (int i = 0; i < row_length; i++) {
    int count = min(row_length, i + 2) - max(0, i - 1);
    auto above = rows[last_row].substr(max(0, i - 1), count);
    if (i == 0) {
      above = "." + above;
    }
    if (i == row_length - 1) {
      above.push_back('.');
    }
    if ((above[0] == '^' && above[1] == '^' && above[2] == '.') ||
        (above[0] == '.' && above[1] == '^' && above[2] == '^') ||
        (above[0] == '^' && above[1] == '.' && above[2] == '.') ||
        (above[0] == '.' && above[1] == '.' && above[2] == '^')) {
      new_row.push_back('^');
    } else {
      new_row.push_back('.');
    }
  }
  rows.push_back(new_row);
}

int count_safe(vector<string> &rows) {
  int count = 0;
  for (auto r : rows) {
    for (char c : r) {
      if (c == '.') {
        count += 1;
      }
    }
  }
  return count;
}

int main(int argc, char **argv) {

  vector<string> rows{};
  rows.push_back(".^^.^.^^^^");
  for (int i = 1; i < 10; i++) {
    add_row(rows);
  }
  cout << "safe: " << count_safe(rows) << endl;

  for (auto &r : rows) {
    cout << r << endl;
  }

  return 0;
}
