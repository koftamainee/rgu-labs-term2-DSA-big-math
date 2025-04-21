#include <cassert>
#include <climits>
#include <iostream>
#include <ostream>

#include "bigint.h"

int main() {
  int arr[] = {53, 6};
  bigint a(arr, 2);
  std::cout << a * 2 << std::endl;
  auto dr = bigint::division(a * 2, 2);
  std::cout << dr.quotient() << " " << dr.remainder() << std::endl;

  // int arr[] = {INT_MIN, -1};
  // bigint a = INT_MIN;
  // bigint b = INT_MIN;
  // b.negate();
  // std::cout << a << " + " << b << std::endl;
  // std::cout << a + b << std::endl;

  // int arr[] = {INT_MIN, 0};
  // bigint a(arr, 2);
  // for (int i = 0; i < 128; ++i) {
  //   std::cout << (a >>= 1) << std::endl;
  // }
}
