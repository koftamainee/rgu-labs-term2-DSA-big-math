#include <cassert>
#include <climits>
#include <exception>
#include <iostream>
#include <ostream>

#include "bigint.h"

int main() {
  // bigint a = INT_MIN;
  // int coeff = 2;
  // a *= coeff;
  // std::cout << a << std::endl;
  // auto dr = bigint::division(a, coeff);
  // std::cout << dr.quotient() << " " << dr.remainder() << std::endl;
  // std::cout << a << std::endl;
  //
  // bigint a = INT_MIN;
  // while (a > 0) {
  //   auto dr = bigint::division(a, 10);
  //   std::cout << a << " / 10 == (" << dr.remainder() << ", " << dr.quotient()
  //             << ")" << std::endl;
  //   a = dr.quotient();
  //   getchar();
  // }
  //
  // int arr[] = {1, 2, 3, 4, 5};
  // bigint a(arr, 5);
  // std::cout << a * a << std::endl;

  int arr[] = {INT_MIN, 0};
  bigint a(arr, 2);
  for (int i = 0; i < 128; ++i) {
    std::cout << (a >>= 1) << std::endl;
  }

  // int a = 1 << 31;
  // std::cout << a << std::endl;
  // for (int i = 0; i < 64; ++i) {
  //   std::cout << (a >>= 1) << std::endl;
  // }
}
