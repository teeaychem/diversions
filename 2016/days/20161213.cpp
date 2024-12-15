#include <__bit/popcount.h>
#include <advent/graph.hpp>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;
using namespace advent;

bool wall(int x, int y, int fav) {
  unsigned long long a = x * x + 3 * x + 2 * x * y + y + y * y;
  unsigned long long b = a + fav;
  unsigned int bits = std::popcount(b);
  return (bits % 2) != 0;
}

int node_rep(int x, int y) { return x * 1000 + y; }

int main(int argc, char **argv) {

  graph::StarGraph<int> test{};
  test.add_edge(graph::WeightedEdge<int>{.from = 1, .to = 3, .cost = 6});
  test.add_edge(graph::WeightedEdge<int>{.from = 1, .to = 2, .cost = 3});
  test.add_edge(graph::WeightedEdge<int>{.from = 1, .to = 4, .cost = 5});
  test.add_edge(graph::WeightedEdge<int>{.from = 2, .to = 3, .cost = 4});
  test.add_edge(graph::WeightedEdge<int>{.from = 2, .to = 6, .cost = 7});
  test.add_edge(graph::WeightedEdge<int>{.from = 1, .to = 6, .cost = 4});
  test.add_edge(graph::WeightedEdge<int>{.from = 1, .to = 7, .cost = 1});
  test.add_edge(graph::WeightedEdge<int>{.from = 7, .to = 5, .cost = 2});
  test.add_edge(graph::WeightedEdge<int>{.from = 5, .to = 6, .cost = 0});

  auto empty_h = [](int node) { return 0.0; };

  auto test_cost_path = test.a_star(1, 6, empty_h);
  if (test_cost_path.has_value()) {
    cout << "cost: " << test_cost_path.value().first << endl;
    for (auto x : test_cost_path.value().second) {
      cout << " + " << x << endl;
    }
  }

  int x_max = 256;
  int y_max = 256;

  cout << "  ";
  for (int x = 0; x < x_max; x++) {
    cout << x;
  }
  cout << endl;
  for (int y = 0; y < y_max; y++) {
    cout << y << " ";
    for (int x = 0; x < x_max; x++) {

      if (wall(x, y, 10)) {
        cout << "#";
      } else {

        cout << ".";
      }
    }
    cout << endl;
  }

  int fav = 10;

  graph::StarGraph<int> g{};
  for (int y = 0; y < y_max; y++) {
    for (int x = 0; x < x_max; x++) {
      if (!wall(x, y, fav)) {
        for (auto p : graph::udlr_points(0, x, x_max, 0, y, y_max)) {
          int other_x = p.first;
          int other_y = p.second;
          if (!wall(other_x, other_y, fav)) {
            g.add_edge(
                graph::WeightedEdge<int>{.from = node_rep(x, y),
                                         .to = node_rep(other_x, other_y),
                                         .cost = 1});
            g.add_edge(
                graph::WeightedEdge<int>{.to = node_rep(x, y),
                                         .from = node_rep(other_x, other_y),
                                         .cost = 1});
          }
        }
      }
    }
  }

  auto cost_path = g.a_star(node_rep(1, 1), node_rep(31, 39), empty_h);
  if (cost_path.has_value()) {
    cout << "cost: " << cost_path.value().first << endl;
    for (auto x : cost_path.value().second) {
      cout << " + " << x << endl;
    }
  }

  unordered_set<int> two{};
  for (int y = 0; y < 51; y++) {
    for (int x = 0; x < 51; x++) {
      auto cost_path_two = g.a_star(node_rep(1, 1), node_rep(x, y), empty_h);
      if (cost_path_two.has_value()) {
        cout << "cost " << x << "," << y << " : " << cost_path_two.value().first
             << endl;
        if (cost_path_two.value().first < 51) {
          two.insert(node_rep(x, y));
        }
      }
    }
  }
  cout << "hm: " << two.size() << endl;

  return 0;
}
