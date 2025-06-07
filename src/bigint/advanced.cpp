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
  if (a == 0) {
    return b < 0 ? -b : b;
  }
  if (b == 0) {
    return a < 0 ? -a : a;
  }

  if (a < 0) {
    a = -a;
  }
  if (b < 0) {
    b = -b;
  }

  while (b != 0) {
    bigint temp = b;
    b = a % b;
    a = temp;
  }

  return a;
}

bigint bigint::pow(bigint const &exponent) const {
  if (exponent < bigint(0)) {
    throw std::runtime_error("bigint::pow: Negative exponent not supported");
  }

  if (exponent == bigint(0)) {
    return 1;
  }

  bigint base = *this;
  bigint result(1);
  bigint exp = exponent;

  while (exp > bigint(0)) {
    if (exp % bigint(2) == bigint(1)) {
      result *= base;
    }
    base *= base;
    exp /= bigint(2);
  }

  return result;
}

bigint bigint::mod_pow(bigint exponent, bigint const &modulus) const {
  throw std::runtime_error(
      "bigint::mod_pow(bigint exponent, bigint const &modulus) const {}: Not "
      "implemented");
}
