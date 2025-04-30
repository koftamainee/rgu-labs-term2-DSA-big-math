#include "bigint.h"

int test_bigint();
int test_bigfloat();

bigint fibonacci_iterative(bigint const &n);

int main() {
  // test_bigint();
  int fact = 10000;
  std::cout << "Computing " << fact << "!... " << std::endl;
  // auto res = fibonacci_iterative(100);
  auto res = bigint::factorial(fact);
  std::cout << "Done" << std::endl;

  // std::cout << res << std::endl;

  // bigint a = 52;
  // for (int i = 0; i < 128; ++i) {
  //   a *= a;
  //   std::cout << "counted" << std::endl;
  //   // std::cout << a << std::endl;
  //   getchar();
  // }
}
