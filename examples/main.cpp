#include <cassert>
#include <climits>
#include <iostream>

#include "bigint.h"

/* TODO:
 * 1. FIX ++
 * 2. implement increment/decrement on negatives
 * 3. check division
 */

/* Current Issues:
 * += does not works in one case, check last code block
 * _raw_negative_increment and _raw_negative_decrement should be implemented w/o
 * positive versions
 */

/* NOTE bit shifts:
 * Increments does not work properly, behavior of (x <<= a; x >>= a - 1) isn't
 * equals to (x <<= a - 1), but should, both of them are (probably?) incorrect
 * UPDATE: fixed right shift for positive numbers, but needed to add additional
 * logic to handle negatives
 * UPDATE 2: negative are probably working
 */

/* NOTE division:
 * Division may not work bc of:
 * - Right bit shift
 * - Left bit shift
 * - negate
 *  look up them in this order
 *
 *  Division works on int range, but in overflow it starts to evaluate remainder
 * and shifted_divisor(?) incorrectly, it works on some numbers but i didn't
 * find regularity yet
 */

/* NOTE addition and negate
 * may not work with negative numbers, bc i didn't sure, that current version of
 * _raw_negative_increment and _raw_negative_decrement works properly
 * UPDATE: negate likely works, but += doesn't :(
 */

/* NOTE output in human-readble mode
 * isn't working on all the cases bc of division, sometimes it can output
 * non-digit symbols, sometimes crash program, DO NOT USE IT
 */

int main() {
  // /* Negative remainder ???? should not happens
  //  * proper output does not works bc it ?? */
  // for (int i = 1; i < 9999; ++i) {
  //   bigint a = INT_MAX;
  //   int coeff = i;
  //   a *= coeff;
  //   auto dr = bigint::division(a, i);
  //   std::cout << "i = " << i << std::endl;
  //   std::cout << a << " / " << i << " == (" << dr.quotient() << ", "
  //             << dr.remainder() << ")" << std::endl;
  //   bigint result = ((dr.quotient() * i) + dr.remainder());
  //
  //   std::cout << "result: " << result << ", source: " << a << ", Equals? "
  //             << (result == a ? "true" : "false") << std::endl;
  //   if (result != a) {
  //     getchar();
  //   }
  // }

  // [2147483645, 1] / 3 == (1610612736, -536870915)

  // int arr[] = {2147483645, 1};
  // bigint a(arr, 2);
  // std::cout << "begin div\n";
  // auto dr = bigint::division(a, 3);
  // std::cout << a << std::endl;
  // std::cout << dr.quotient() << ", " << dr.remainder() << std::endl;
  // std::cout << (dr.quotient() * 3) + dr.remainder() << std::endl;

  // /* Quotient became larger instead of smaller, mb bc prev problem, or bug in
  //  * right/left shift idk */
  // bigint a = INT_MAX;
  // a *= INT_MAX;
  // while (a > 0) {
  //   auto dr = bigint::division(a, 10);
  //   std::cout << a << " / 10 == (" << dr.remainder() << ", " << dr.quotient()
  //             << ")" << std::endl;
  //   a = dr.quotient();
  //   // getchar();
  // }

  // /* increments SHOULD REMOVE EXTRA ZEROS */
  // bigint a = INT_MIN;
  // bigint b = INT_MAX;
  // std::cout << --a << " " << ++a << std::endl;
  // std::cout << ++b << " " << --b << std::endl;

  // += isn't working.... again
  // [-1073741827, 0] - 1610612736 = [1610612733, 1]
  int arr[] = {-1073741827, 0};
  bigint a(arr, 2);
  bigint b = 1610612736;
  b.negate();
  std::cout << a << " + " << b << " = " << a + b << std::endl;
}
