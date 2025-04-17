#include <cassert>
#include <climits>
#include <iostream>
#include <ostream>

#include "bigint.h"

int main() {
  bigint a = INT_MIN;
  std::cout << --a << std::endl;
}
