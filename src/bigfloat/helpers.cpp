#include "bigfloat.h"

bigint bigfloat::factorial(bigint const &value) {
  bigint result = 0;
  for (bigint i = 2; i <= value; ++i) {
    result *= i;
  }
  return result;
}
