#include <algorithm>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <limits>
#include <regex>
using namespace std;

struct reindeer_stats {
  string name;
  unsigned int speed;
  unsigned int endurance;
  unsigned int recovery;
};

unsigned int distance(reindeer_stats *the_reindeer, unsigned int time) {
  unsigned int period = the_reindeer->endurance + the_reindeer->recovery;
  unsigned int phases = time / period;
  unsigned int sprint = time % period;
  return (phases * the_reindeer->speed * the_reindeer->endurance) +
         (min(sprint, the_reindeer->endurance) * the_reindeer->speed);
}

int main(int argc, char **argv) {



  if (argc != 3) {
    cout << "A file and time limit is needed for anything else…" << endl;
    exit(0);
  }

  vector<reindeer_stats> stats;

  string the_file = argv[1];
  unsigned int time_limit = stoi(argv[2]);

  ifstream infile(the_file);

  string line;
  regex cmd_regex("([A-Z][a-z]+) can fly (\\d+) km/s for (\\d+) seconds, but "
                  "then must rest for (\\d+) seconds.");
  smatch matches;

  for (string line; getline(infile, line);) {
    if (regex_search(line, matches, cmd_regex)) {

      reindeer_stats new_deer = {
          .name = matches[1],
          .speed = static_cast<unsigned int>(stoi(matches[2])),
          .endurance = static_cast<unsigned int>(stoi(matches[3])),
          .recovery = static_cast<unsigned int>(stoi(matches[4])),
      };
      stats.push_back(new_deer);

    } else {
      cout << "x_x" << endl;
      exit(1);
    }
  }

  unsigned int furthest = numeric_limits<unsigned int>::min();
  for (auto r : stats) {
    unsigned int travelled = distance(&r, time_limit);
    cout << r.name << "\t" << travelled << endl;
    if (travelled > furthest) {
      furthest = travelled;
    }
  }
  cout << endl;

  vector<int> points = vector(stats.size(), 0);
  for (unsigned int i = 0; i < time_limit; i++) {
    unsigned int furthest = numeric_limits<unsigned int>::min();
    vector<unsigned int> travelled{};
    for (size_t d = 0; d < stats.size(); d++) {
      unsigned int went = distance(&stats[d], i + 1);
      travelled.push_back(went);
      if (went >= furthest) {
        furthest = went;
      }
    }
    for (size_t d = 0; d < stats.size(); d++) {
      if (travelled[d] == furthest) {
        points[d] += 1;
      }
    }
  }

  int most_points{0};
  for (size_t p = 0; p < stats.size(); p++) {
    cout << stats[p].name << "\t" << points[p] << endl;
    if (points[p] > most_points) {
      most_points = points[p];
    }
  }

  cout << endl;
  cout << "furthest:\t" << furthest << endl;
  cout << "most points:\t" << most_points << endl;

  return 0;
}
