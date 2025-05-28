#include <BigInt.hpp>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

void large_sum(ifstream &infile) {

  BigInt::Int big_sum = BigInt::Int("0");

  for (string line; getline(infile, line);) {
    big_sum = big_sum + BigInt::Int(line);
  }

  cout << big_sum << "\n";


}
