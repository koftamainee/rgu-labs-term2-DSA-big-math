#include "bigint.h"

int test_bigint();
int test_bigfloat();

bigint fibonacci_iterative(bigint const &n);

int main() {
  // test_bigint();

  std::cout << "Computing hyuinya... " << std::endl;
  auto res = fibonacci_iterative(100000);
  // auto res = bigint::factorial(4000);
  std::cout << "Done" << std::endl;

  // std::cout << res << std::endl;

  // bigint a = 0;
  // std::cout << --a << std::endl;
}
