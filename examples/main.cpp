#include <cassert>
#include <climits>
#include <iostream>

#include "bigint.h"

int main() {
  // /* Negative remainder ???? should not happens
  //  * proper output does not works bc it ?? */
  // bigint a = INT_MAX;
  // int coeff = 999999999;
  // a *= coeff;
  // std::cout << a << std::endl;
  // auto dr = bigint::division(a, 52);
  // std::cout << dr.quotient() << " " << dr.remainder() << std::endl;

  // /* Quotient became larger instead of smaller, mb bc prev problem, or bug in
  //  * right/left shift idk */
  // bigint a = INT_MAX;
  // while (a > 0) {
  //   auto dr = bigint::division(a * 15, 10);
  //   std::cout << a << " / 10 == (" << dr.remainder() << ", " << dr.quotient()
  //             << ")" << std::endl;
  //   a = dr.quotient();
  //   getchar();
  // }

  // /* Should it be [-1, 0] all the time with shift higher then 32 ??? */
  // int arr[] = {INT_MIN, 0};
  // bigint a(arr, 2);
  // for (int i = 0; i < 128; ++i) {
  //   std::cout << (a >>= 1) << std::endl;
  // }
}
