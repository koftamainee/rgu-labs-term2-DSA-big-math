#include <climits>
#include <iostream>
#include <ostream>

#include "bigint.h"

int main() {
  bigint a = 500;

  a.negate();
  auto opt = a.to_int();
  if (opt) {
    std::cout << *opt << std::endl;
  } else {
    std::cout << "error" << std::endl;
  }

  // a.negate();
  // opt = a.to_int();
  // if (opt) {
  //   std::cout << *opt << std::endl;
  // } else {
  //   std::cout << "error" << std::endl;
  // }
}
