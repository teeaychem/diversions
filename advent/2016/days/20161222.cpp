#include <advent/combinatorics.hpp>
#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <vector>

using namespace std;

struct node {
  int x;
  int y;
  int size;
  int used;
  int avail;
  bool ex = false;

  string print() {
    stringstream ss{};
    ss << x << "," << y;
    ss << "\tsize: " << size;
    ss << "\tused: " << used;
    ss << "\tavail: " << avail;
    return ss.str();
  }
};

void swap(node &a, node &b) {
  int a_s = a.size;
  a.size = b.size;
  b.size = a_s;

  int a_u = a.used;
  a.used = b.used;
  b.used = a_u;

  int a_a = a.avail;
  a.avail = b.avail;
  b.avail = a_a;

  int a_ex = a.ex;
  a.ex = b.ex;
  b.ex = a_ex;
}

void swap_nodes(int a_x, int a_y, int b_x, int b_y, vector<node> &nodes) {
  for (auto &a : nodes) {
    if (a.x == a_x && a.y == a_y) {
      for (auto &b : nodes) {
        if (b.x == b_x && b.y == b_y) {
          swap(a, b);
          return;
        }
      }
    }
  }
}

void part_a(vector<node> nodes) {

  auto node_pairs = advent::combinatorics::size_k_vectors(nodes, 2);
  int count = 0;
  for (auto p : node_pairs) {
    bool distinct = p[0].x != p[1].x || p[0].y != p[1].y;
    bool a_ne = p[0].used != 0;
    bool a_fit = p[0].used <= p[1].avail;

    bool b_ne = p[1].used != 0;
    bool b_fit = p[1].used <= p[0].avail;
    if (distinct && a_ne && a_fit) {
      count += 1;
    }
    if (distinct && b_ne && b_fit) {
      count += 1;
    }
  }
  cout << count << " (" << node_pairs.size() << ")" << endl;
}

void print_nodes(vector<node> &nodes) {
  cout << "   ";
  for (int x = 0; x < 30; x++) {
    if (x < 10) {
      cout << x << "  ";
    } else {
      cout << x << " ";
    }
  }
  cout << endl;
  for (int y = 0; y < 32; y++) {
    if (y < 10) {
      cout << y << "  ";
    } else {
      cout << y << " ";
    }
    for (int x = 0; x < 30; x++) {
      for (auto n : nodes) {
        if (n.x == x && n.y == y) {
          if (n.size > 100) {
            cout << " # ";
          } else if (n.used == 0) {
            cout << " _ ";
          } else if (n.ex) {
            cout << " x ";
          } else {
            cout << " . ";
          }
        }
      }
    }
    cout << endl;
  }
}

int main(int argc, char **argv) {

  vector<node> nodes{};

  string the_file = argv[1];
  ifstream infile(the_file);

  string line;

  regex a("/dev/grid/"
          "node-x(\\d+)-y(\\d+)\\s+(\\d+)T\\s+(\\d+)T\\s+(\\d+)T\\s+(\\d+)%");
  smatch matches;

  for (string line; getline(infile, line);) {
    if (regex_search(line, matches, a)) {
      node new_node = node{.x = stoi(matches[1]),
                           .y = stoi(matches[2]),
                           .size = stoi(matches[3]),
                           .used = stoi(matches[4]),
                           .avail = stoi(matches[5])};
      nodes.push_back(new_node);
    } else {
      cout << line << endl;
    }
  }
  // part_a(nodes);

  int start_x = 29;
  int start_y = 0;

  int end_x = 0;
  int end_y = 0;

  for (auto &n : nodes) {
    if (n.x == 29 && n.y == 0) {
      n.ex = true;
    }
  }

  int count = 0;

  print_nodes(nodes);
  for (int i = 11; 7 < i; i--) {
    swap_nodes(i, 22, i - 1, 22, nodes);
    count++;
  }
  for (int i = 22; 0 < i; i--) {
    swap_nodes(7, i, 7, i - 1, nodes);
    count++;
  }
  for (int i = 7; i < 28; i++) {
    swap_nodes(i, 0, i + 1, 0, nodes);
    count++;
  }
  int x = 28;
  for (int i = 0; i < 28; i++) {
    swap_nodes(x, 0, x + 1, 0, nodes);
    count++;
    swap_nodes(x + 1, 0, x + 1, 1, nodes);
    count++;
    swap_nodes(x, 1, x + 1, 1, nodes);
    count++;
    swap_nodes(x - 1, 1, x, 1, nodes);
    count++;
    swap_nodes(x - 1, 0, x - 1, 1, nodes);
    count++;
    x = x - 1;
  }

  print_nodes(nodes);
  cout << count << endl;

  return 0;
}
