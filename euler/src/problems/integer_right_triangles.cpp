#include <cstdint>
#include <deque>
#include <iostream>
#include <sstream>
using namespace std;

/*
  Very messy.

The idea is to use the three of primitive pythagorean triples.

Details: https://en.wikipedia.org/wiki/Tree_of_primitive_Pythagorean_triples

Found while searching for a way to generate pythagorean triples.
Though, generation only gives primitive triples.
So, each triple is scaled until its perimeter would exceed 1000.
*/

struct Triangle {
  int64_t a;
  int64_t b;
  int64_t c;

  string string() {
    stringstream ss{};

    ss << a << " " << b << " " << c << "(" << perimeter() << ")";
    return ss.str();
  }

  int64_t perimeter() { return a + b + c; }

  Triangle scale(int64_t x) {

    Triangle scaled = {
        .a = x * a,
        .b = x * b,
        .c = x * c};

    return scaled;
  }

  Triangle child_a() {

    Triangle child = {
        .a = a + -2 * b + 2 * c,
        .b = 2 * a + -b + 2 * c,
        .c = 2 * a + -2 * b + 3 * c};

    return child;
  }

  Triangle child_b() {

    Triangle child = {
        .a = a + 2 * b + 2 * c,
        .b = 2 * a + b + 2 * c,
        .c = 2 * a + 2 * b + 3 * c};

    return child;
  }

  Triangle child_c() {

    Triangle child = {
        .a = -a + 2 * b + 2 * c,
        .b = -2 * a + b + 2 * c,
        .c = -2 * a + 2 * b + 3 * c};

    return child;
  }
};

void integer_right_triangles() {

  size_t solution_counts[1001];
  for (size_t i{0}; i <= 1000; ++i) {
    solution_counts[i] = 0;
  }

  Triangle initial = {3, 4, 5};

  deque<Triangle> tq{};
  tq.push_back(initial);

  while (!tq.empty()) {
    Triangle next = tq.front();

    tq.pop_front();

    int64_t p = next.perimeter();

    if (p <= 1000) {

      Triangle scaled = next;

      for (int64_t scale{1}; scaled.perimeter() <= 1000; ++scale) {
        solution_counts[scaled.perimeter()]++;
        scaled = next.scale(scale);
      }

      tq.push_back(next.child_a());
      tq.push_back(next.child_b());
      tq.push_back(next.child_c());
    }
  }

  int64_t max_p{0};
  size_t max_count{0};

  for (int64_t i{0}; i <= 1000; ++i) {
    if (max_count < solution_counts[i]) {
      max_p = i;
      max_count = solution_counts[i];
    }
  }

  cout << max_p << "\n";
}
