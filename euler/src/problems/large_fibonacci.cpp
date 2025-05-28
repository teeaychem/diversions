
#include <BigInt.hpp>
#include <iostream>

using namespace std;

void large_fibonacci() {
  size_t index{2};
  BigInt::Int a{1};
  BigInt::Int b{1};
  BigInt::Int c{1};

  while (b.size() < 1000) {
    cout << "F_{" << index << "} = " << b << "\n";
    c = a + b;
    a = b;
    b = c;
    index++;
  }

  cout << "F_{" << index << "} = " << b << "\n";
}
