#include <cassert>
#include <climits>
#include <iostream>
#include <ostream>

#include "bigint.h"

int main() {
  int arr[] = {1, 2};
  bigint a = INT_MAX;
  a *= INT_MAX;

  std::cout << a * a << std::endl;
}
