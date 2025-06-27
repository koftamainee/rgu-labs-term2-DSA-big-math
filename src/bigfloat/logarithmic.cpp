#include <stdexcept>

#include "bigfloat.h"

bigfloat log_taylor_series(const bigfloat &x, const bigfloat &EPS) {
  bigfloat w = (x - bigfloat(1)) / (x + bigfloat(1));
  bigfloat w_squared = w * w;
  bigfloat term = w;
  bigfloat result = w;
  bigfloat n = bigfloat(3);

  while (term.abs() > EPS) {
    term *= w_squared;
    result += term / n;
    n += bigfloat(2);
  }

  return result * bigfloat(2);
}

bigfloat log(bigfloat const &number, bigfloat const &EPS) {
  if (number <= bigfloat(0)) {
    throw std::invalid_argument("logarithm of non-positive number");
  }

  bigfloat x = number;
  bigint k = 0;

  while (x > bigfloat(1)) {
    x /= bigfloat(2);
    ++k;
  }
  while (x < bigfloat(1, 2)) {
    x *= bigfloat(2);
    --k;
  }

  static bigfloat ln2 = log_taylor_series(bigfloat(2), EPS);
  return log_taylor_series(x, EPS) + bigfloat(k) * ln2;
}

bigfloat log2(bigfloat const &number, bigfloat const &EPS) {
  bigfloat ln2 = log(2, EPS);
  return log(number, EPS) / ln2;
}

bigfloat log10(bigfloat const &number, bigfloat const &EPS) {
  if (number <= bigfloat(0)) {
    throw std::invalid_argument("logarithm of non-positive number");
  }

  bigfloat ln10 = log(bigfloat(10), EPS);

  return log(number, EPS) / ln10;
}
