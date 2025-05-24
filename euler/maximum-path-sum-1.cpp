#include <cstdio>
#include <vector>
using std::vector;

using namespace std;

int main(int argc, char *argv[]) {

  vector<vector<int>> triangle = {
      {1},
      {2, 3},
      {4, 5, 6},
  };

  // Work backwards taking the optimal move each step.
  for (int i = triangle.size() - 2; 0 <= i; --i) {
    for (int j = 0; j < triangle[i].size(); ++j) {
      triangle[i][j] += max(triangle[i + 1][j], triangle[i + 1][j + 1]);
    }
  }

  printf("The maximum path through the triangle totals: %d\n",
         triangle[0][0]);
}
