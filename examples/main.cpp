#include <cassert>
#include <climits>
#include <fstream>
#include <iostream>
#include <ostream>

#include "bigint.h"

int main() {
  bigint a = INT_MAX;
  bigint b = 1;
  std::cout << a + b << std::endl;
}
