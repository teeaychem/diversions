#include <cvc5/cvc5.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
using namespace cvc5;

int main(int argc, char **argv) {

  TermManager tm;
  Solver solver = Solver(tm);

  solver.setOption("produce-models", "true");

  Term a = tm.mkConst(tm.getIntegerSort(), "a");
  Term b = tm.mkConst(tm.getIntegerSort(), "b");
  Term c = tm.mkConst(tm.getIntegerSort(), "c");

  Term a_sq = tm.mkTerm(Kind::MULT, {a, a});
  Term b_sq = tm.mkTerm(Kind::MULT, {b, b});
  Term c_sq = tm.mkTerm(Kind::MULT, {c, c});

  Term equal =
      tm.mkTerm(Kind::EQUAL, {tm.mkTerm(Kind::ADD, {a_sq, b_sq}), c_sq});
  solver.assertFormula(equal);

  Term target = tm.mkTerm(
      Kind::EQUAL, {tm.mkTerm(Kind::ADD, {a, b, c}), tm.mkInteger(1000)});
  solver.assertFormula(target);

  Term a_lt_b = tm.mkTerm(Kind::LT, {a, b});

  solver.assertFormula(a_lt_b);

  Term b_lt_c = tm.mkTerm(Kind::LT, {b, c});

  solver.assertFormula(b_lt_c);

  solver.assertFormula(tm.mkTerm(Kind::LT, {tm.mkInteger(0), a}));
  solver.assertFormula(tm.mkTerm(Kind::LT, {tm.mkInteger(0), b}));
  solver.assertFormula(tm.mkTerm(Kind::LT, {tm.mkInteger(0), c}));

  auto result = solver.checkSat();
  cout << result << endl;
  cout << solver.getModel({}, {a, b, c});

  return 0;
}
