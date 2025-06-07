
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
  //
  // bigfloat pi_4 = bigfloat::PI() / 4;
  //
  // std::cout << "π/4 = " << pi_4.to_decimal() << std::endl;
  // std::cout << "sin(π/4) =  " << sin(pi_4).to_decimal() << std::endl;
  // std::cout << "cos(π/4) = " << cos(pi_4).to_decimal() << std::endl;
  // std::cout << "tg(π/4) = " << tg(pi_4).to_decimal() << std::endl;
  // std::cout << "arctg(π/4) = " << arctg(pi_4).to_decimal() << std::endl;
  // std::cout << "arcctg(π/4) = " << arcctg(pi_4).to_decimal() << std::endl;
  // std::cout << "arcsin(π/4) = " << arcsin(pi_4).to_decimal() << std::endl;
  // std::cout << "arccos(π/4) = " << arccos(pi_4).to_decimal() << std::endl;

  std::cout << "sin(12) = " << sin(200).to_decimal() << std::endl;

  return 0;
}
