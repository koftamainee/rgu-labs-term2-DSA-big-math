#include <cassert>
#include <climits>
#include <iostream>

#include "bigint.h"

int main() {
  /* Negative remainder ???? should not happens
   * proper output does not works bc it ?? */
  bigint a = INT_MAX - 1;
  int coeff = INT_MAX;
  // a *= coeff;
  std::cout << a << std::endl;
  auto dr = bigint::division(a, 2);
  std::cout << dr.quotient() << " " << dr.remainder() << std::endl;
  std::cout << "result: " << (dr.quotient() * 2 + dr.remainder())
            << ", source: " << a << std::endl;

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

  // int arr[] = {1147483649, 9266431};
  // int arr2[] = {0, 13631488};
  // bigint a(arr, 2);
  // bigint b(arr2, 2);
  // bigint result = a - b;
  // std::cout << a << " - " << b << " = " << result << std::endl;
  //
  // std::cout << "\n\n" << (a > b) << " " << (result <= a) << std::endl;

  // /* increments SHOULD REMOVE EXTRA ZEROS */
  // bigint a = INT_MIN;
  // bigint b = INT_MAX;
  // std::cout << --a << " " << ++a << std::endl;
  // std::cout << ++b << " " << --b << std::endl;
}

/* Current Issues:
 * Negative remainder on dividing very big numbers
 * Increments and decrements should remove unsignificant numbers
 * Increments and decrements should not use +=
 */
