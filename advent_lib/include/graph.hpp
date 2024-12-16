#include <__algorithm/ranges_reverse.h>
#include <cctype>
#include <cstdio>
#include <functional>
#include <iostream>
#include <optional>
#include <ostream>
#include <queue>
#include <set>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

namespace advent {
namespace graph {

typedef float cost_t;

template <typename node_t> struct WeightedEdge {
  node_t from;
  node_t to;
  cost_t cost;
};

template <typename node_t> std::function<cost_t(node_t)> heuristic;

template <typename node_t> struct DiscoveredNode {
  node_t id;
  cost_t estimate;
  cost_t cheapest;
  optional<node_t> source;
};

template <typename node_t>
inline bool operator<(WeightedEdge<node_t> const &lhs,
                      WeightedEdge<node_t> const &rhs) {
  if (lhs.from != rhs.from) {
    return lhs.from < rhs.from;
  } else {
    return lhs.to < rhs.to;
  }
}

template <typename node_t>
inline bool operator<(WeightedEdge<node_t> const &e, node_t const &id) {
  return e.from < id;
}

template <typename node_t>
inline bool operator<(node_t const &id, WeightedEdge<node_t> const &e) {
  return id < e.from;
}

template <typename node_t>
inline bool operator<(DiscoveredNode<node_t> const &lhs,
                      DiscoveredNode<node_t> const &rhs) {
  return lhs.id < rhs.id;
}

template <typename node_t>
inline bool operator<(DiscoveredNode<node_t> const &e, node_t const &id) {
  return e.id < id;
}

template <typename node_t>
inline bool operator<(node_t const &id, DiscoveredNode<node_t> const &e) {
  return id < e.id;
}

template <typename node_t> class StarGraph {
public:
  set<WeightedEdge<node_t>, std::less<>> graph_set;

public:
  bool add_edge(WeightedEdge<node_t> e) {
    if (graph_set.contains(e)) {
      return false;
    } else {
      graph_set.insert(e);
      return true;
    }
  }

  optional<pair<int, vector<node_t>>> a_star(node_t start, std::function<bool(node_t)> goal_f,
                                             std::function<cost_t(node_t)> h) {

    set<DiscoveredNode<node_t>, std::less<>> unexplored_nodes{};
    set<DiscoveredNode<node_t>, std::less<>> explored_nodes{};
    unordered_set<node_t> seen_nodes;

    auto cheaper = [&unexplored_nodes, &explored_nodes](node_t a, node_t b) {
      auto unexplored_a = unexplored_nodes.find(a);
      if (unexplored_a == unexplored_nodes.end()) {
        return false;
      }
      auto unexplored_b = unexplored_nodes.find(b);
      if (unexplored_a == unexplored_nodes.end()) {
        return true;
      }

      return unexplored_a->estimate > unexplored_b->estimate; // max heap
    };
    priority_queue<node_t, vector<node_t>, decltype(cheaper)> the_queue(
        cheaper);

    unexplored_nodes.insert(DiscoveredNode<node_t>{
        .id = start, .estimate = h(start), .cheapest = 0, .source = nullopt});
    the_queue.emplace(start);

    while (!the_queue.empty()) {
      node_t current = the_queue.top();
      if (goal_f(current)) {
        DiscoveredNode<node_t> the_last;
        the_last = *unexplored_nodes.find(current);
        auto the_cost = the_last.cheapest;

        vector<node_t> the_path{};

        while (the_last.source != nullopt) {
          the_path.push_back(the_last.source.value());
          the_last = *explored_nodes.find(the_last.source);
        }

        ranges::reverse(the_path.begin(), the_path.end());

        return make_pair(the_cost, the_path);
      }
      the_queue.pop();

      if (explored_nodes.find(current) == explored_nodes.end()) {

        auto current_discovery = unexplored_nodes.find(current);

        if (current_discovery == unexplored_nodes.end()) {
          cout << "missing node" << endl;
          exit(1);
        }

        explored_nodes.insert(unexplored_nodes.extract(current_discovery));

        auto out_edge = graph_set.find(current);
        // Cost known_cheapest = numeric_limits<Cost>::max();
        while (out_edge != graph_set.end()) {
          if (out_edge->from != current) {
            break;
          }

          node_t neighbour_id = out_edge->to;
          auto neighbour_discovery = unexplored_nodes.find(neighbour_id);
          cost_t this_edge_cost = current_discovery->cheapest + out_edge->cost;
          if (neighbour_discovery == unexplored_nodes.end()) {

            unexplored_nodes.insert(DiscoveredNode<node_t>{
                .id = neighbour_id,
                .estimate = this_edge_cost + h(neighbour_id),
                .cheapest = this_edge_cost,
                .source = optional(current),
            });
            the_queue.emplace(neighbour_id);

          } else {
            if (this_edge_cost < neighbour_discovery->cheapest) {

              DiscoveredNode extracted = std::move(
                  unexplored_nodes.extract(neighbour_discovery).value());

              extracted.source = optional(current);
              extracted.cheapest = this_edge_cost;
              extracted.estimate = this_edge_cost + h(neighbour_id),

              unexplored_nodes.insert(extracted);

              the_queue.emplace(neighbour_id);
            }
          }
          out_edge++;
        }
      }
    }
    return nullopt;
  }
};

vector<pair<int, int>> surrounding_points(int x_min, int x, int x_max, //
                                          int y_min, int y, int y_max) {
  vector<pair<int, int>> surrounding{};
  for (int y_i = max(y_min, y - 1); y_i <= min(y + 1, y_max); y_i++) {
    for (int x_i = max(x_min, x - 1); x_i <= min(x + 1, x_max); x_i++) {
      if (y != y_i || x != x_i) {
        surrounding.push_back(make_pair(x_i, y_i));
      }
    }
  }
  return surrounding;
}

vector<pair<int, int>> udlr_points(int x_min, int x, int x_max, //
                                   int y_min, int y, int y_max) {
  vector<pair<int, int>> surrounding{};
  if (y_min < y) {
    surrounding.push_back(pair(x, y - 1));
  }
  if (y < y_max) {
    surrounding.push_back(pair(x, y + 1));
  }
  if (x_min < x) {
    surrounding.push_back(pair(x - 1, y));
  }
  if (x < x_max) {
    surrounding.push_back(pair(x + 1, y));
  }

  return surrounding;
}

} // namespace graph
} // namespace advent
