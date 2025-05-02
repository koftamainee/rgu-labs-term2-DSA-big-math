#include <stdexcept>

#include "bigint.h"

bigint bigint::product(const bigint &l, const bigint &r) {
  if (l > r) {
    return 1;
  }
  if (l == r) {
    return l;
  }
  if (r - l == 1) {
    return l * r;
  }

  bigint m = (l + r) / 2;
  return product(l, m) * product(m + 1, r);
}

bigint bigint::factorial(const bigint &n) {
  if (n < 2) {
    return 1;
  }
  return product(2, n);
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
