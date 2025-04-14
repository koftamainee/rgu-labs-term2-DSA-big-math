#include <climits>
#include <iostream>
#include <ostream>

#include "bigint.h"

int main() {
  int arr[] = {-5, 2, 4, 5, 6, 7, 8, 9, INT_MIN};
  bigint a = -5;

  std::cout << a << std::endl;

  --a;

  std::cout << a << std::endl;

  // auto opt = a.to_int();
  // if (opt) {
  //   std::cout << *opt << std::endl;
  // } else {
  //   std::cout << "error" << std::endl;
  // }

  // a.negate();
  // opt = a.to_int();
  // if (opt) {
  //   std::cout << *opt << std::endl;
  // } else {
  //   std::cout << "error" << std::endl;
  // }
}
