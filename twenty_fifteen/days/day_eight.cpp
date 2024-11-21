#include <cctype>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <ostream>
#include <regex>
#include <string>

using namespace std;

int main(int argc, char **argv) {

  string file = argv[1];

  unsigned long count = 0;

  string out_buffer;
  ifstream ins(file);
  char c;
  string the_string;

  while ((c = ins.get())) {
    if (c == EOF) {
      break;
    }
    if (!isspace(c)) {
      count += 1;
      the_string.push_back(c);
    }
  }

  string replaced = the_string;
  regex escape_regex("(\\\\(\\\\|\"|\'))");
  regex something_regex("(\\\\x[0-9a-f][0-9a-f])");
  regex quote_regex("(\")");
  regex slash_regex("(\\\\)");
  replaced = regex_replace(replaced, escape_regex, "*");
  replaced = regex_replace(replaced, something_regex, "?");
  replaced = regex_replace(replaced, quote_regex, "");
  cout << count - the_string.length() << endl;

  int q_count = 0;
  int s_count = 0;

  regex_token_iterator<string::iterator> regex_end;

  ifstream infile(file);
  for (string line; getline(infile, line);) {
    int local_q_count = 0;
    regex_token_iterator quotes(line.begin(), line.end(), quote_regex);
    while (quotes != regex_end) {
      local_q_count += 1;
      quotes++;
    }
    int local_s_count = 0;
    regex_token_iterator slashes(line.begin(), line.end(), slash_regex);
    while (slashes != regex_end) {
      local_s_count += 1;
      slashes++;
    }
    cout << local_q_count << " " << local_s_count << " " << line << endl;
    q_count += local_q_count + 2;
    s_count += local_s_count;
  }
  int fresh = (q_count + s_count + the_string.length());

  cout << fresh - count << endl;
}
