
#include "bigfloat.h"
#include "bigint.h"

int test_bigint();
int test_bigfloat();
int bigint_performance();

bigint fibonacci_iterative(bigint const &n);

int main() {
  // bigint_performance();
  // test_bigint();
  // test_bigfloat();

  bigfloat a(22, 7);

  std::cout << sin(a) << std::endl;
  std::cout << cos(a) << std::endl;

  // bigfloat res("-13318024705766", "10712533435649955");
  // bigfloat term("-6075997337331856", "275579922632095092375");

  // std::cout << res << " + " << term << " = " << res + term << std::endl;

  return 0;
}
