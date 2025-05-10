#include <stdexcept>

#include "bigint.h"

bigint bigint::factorial(const bigint &n) {
  if (n < 2) {
    return 1;
  }

  bigint result = 1;
  for (bigint i = 2; i <= n; ++i) {
    result *= i;
  }

  return result;
}

bigint bigint::gcd(bigint a, bigint b) {
  a = a < 0 ? -a : a;
  b = b < 0 ? -b : b;

  if (a == 0) {
    return b;
  }
  if (b == 0) {
    return a;
  }

  int shift = 0;
  while (((a | b) & 1) == 0) {
    a >>= 1;
    b >>= 1;
    ++shift;
  }

  while ((a & 1) == 0) {
    a >>= 1;
  }

  do {
    while ((b & 1) == 0) {
      b >>= 1;
    }
    if (a > b) {
      auto temp = a;
      a = b;
      b = temp;
    }
    b -= a;
  } while (b != 0);

  return a << shift;
}

bigint bigint::pow(bigint const &exponent) const {}

bigint bigint::mod_pow(bigint exponent, bigint const &modulus) const {}
