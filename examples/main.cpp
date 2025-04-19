#include <cassert>
#include <climits>
#include <iostream>
#include <ostream>

#include "bigint.h"

int main() {
  int arr[] = {1, INT_MAX, 3};
  bigint a = 5;
  for (int i = 0; i < 64; ++i) {
    std::cout << a << " >> " << i << " = " << ((a >> i) >> i) << std::endl;
  }
}
