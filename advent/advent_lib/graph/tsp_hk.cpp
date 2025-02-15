#include <climits>
#include <functional>
#include <iostream>
#include <limits>
#include <map>
#include <vector>

using namespace std;

typedef unsigned int Distance;
typedef unsigned int BitSet;
typedef vector<vector<unsigned int>> AdjGraph;
typedef unsigned int Vertex;
typedef std::function<Distance(Vertex, Vertex)> distance_between_nodes;

// a rough pass at the held–karp algorithm
// https://en.wikipedia.org/wiki/Held%E2%80%93Karp_algorithm

// to transform a node index i to the BitSet representation of a singleton
// set of the node, take 2^i, as in binary (exclusively )the ith position
// is 1. pow(2, i)  == 1 << i
BitSet singleton_of(Vertex node) { return 1 << node; }

bool element_of(Vertex node, BitSet set) { return set & singleton_of(node); }

BitSet subset_minus(BitSet set, Vertex node) {
  return set ^ singleton_of(node);
}

/// we only need to know how many nodes there are and a way to obtain the
/// distance of the shortest path between two nodes.
Distance tsp(unsigned long n, distance_between_nodes shorest_distance) {

  // count of how many (sub)sets of nodes there are
  unsigned int subsets = pow(2, n - 1);

  // shortest[visited_subset][last_node] = shortest known distance through the
  // visited subset ending at last_node
  // this will contain many redundant cells, as not every possible last node
  // will be a node that's been visited. still, it is simple to skip over these
  vector<vector<Distance>> shortest(
      subsets, vector<Distance>(n - 1, numeric_limits<Distance>::max()));

  // go through each possible subset, and each possible last node, and update
  // the shortest path
  // note, e.g. BitSet(1) = b001, BitSet(2) = b10 and BitSet(3) = b11, so proper
  // subsets of a set are visited before a set is visited
  for (BitSet visited = 1; visited < subsets; visited++) {
    // visited is the binary representation of a set, by contrast 'last_node' is
    // the numerical index of a node
    for (Vertex last_node = 0; last_node < (n - 1); last_node++) {

      // we are indiscriminately examining all nodes which may have been the
      // previous node visited before acheiving the visited set.
      // so, a check is made to ensure the last node was a visited node.
      if (!(element_of(last_node, visited))) {
        continue;
      }

      if (visited == singleton_of(last_node)) {
        // if this is a singleton set, use the shortest direct path
        shortest[visited][last_node] = shorest_distance(n - 1, last_node);

      } else {
        // otherwise, consider the rest of the nodes in the set,
        // to get to the last node, some path was taken from some origin node
        BitSet without_last_node = subset_minus(visited, last_node);
        // the known shortest distance for a smaller subset of nodes has already
        // been established, so the shortest way to vist all the nodes in
        // visited and to finish on the specified last node is a matter of
        // selecting the appropriate origin node

        // note, that smaller sets have been established is guaranteed by:
        // 1. using the shortest_direct for singleton sets
        // 2. the chosen representation ensuring that:
        // if a is a strict subset of b then (BitSet) a < (BitSet) b
        // (see above)
        for (Vertex last_source = 0; last_source < n - 1; last_source++) {
          if (!(element_of(last_source, without_last_node))) {
            continue;
          }
          shortest[visited][last_node] =
              min(shortest[visited][last_node],
                  shortest[without_last_node][last_source] +
                      shorest_distance(last_source, last_node));
        }
      }
    }
  }

  // finally, take the minimum distance by inspecting the distances of all
  // possible final steps
  Distance shortest_distance = numeric_limits<Distance>::max();
  for (unsigned int last_node = 0; last_node < n - 1; last_node++) {
    shortest_distance =
        min(shortest_distance, shortest[subsets - 1][last_node] +
                                   shorest_distance(last_node, n - 1));
  }

  return shortest_distance;
}

int main() {

  map<Vertex, map<Vertex, Distance>> test_distances{};
  auto shortest_test = [&test_distances](Vertex a, Vertex b) {
    if (test_distances.find(a) != test_distances.end() &&
        test_distances[a].find(b) != test_distances[a].end()) {
      cout << a << " <-> " << b << " = " << test_distances[a][b] << endl;
      return test_distances[a][b];
    } else if (test_distances.find(b) != test_distances.end() &&
               test_distances[b].find(a) != test_distances[b].end()) {
      cout << a << " <-> " << b << " = " << test_distances[b][a] << endl;
      return test_distances[b][a];
    } else {
      cout << "oh " << a << " " << b << endl;
      return numeric_limits<Distance>::max();
    }
  };
  test_distances[0][1] = 1;
  test_distances[1][2] = 7;
  test_distances[1][3] = 9;
  test_distances[1][4] = 2;
  test_distances[2][3] = 1;
  test_distances[3][4] = 1;
  test_distances[0][3] = 7;

  cout << "shortest: " << tsp(test_distances.size(), shortest_test) << endl;
}
