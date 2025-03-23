#include <stdexcept>

#include "bigfloat.h"

bigfloat pow(bigfloat const &base, bigint const &exp) {
  if (exp == 0) {
    return 1;
  }
  if (exp < 0) {
    return 1 / pow(base, -exp);
  }
  bigfloat result = 1;
  bigfloat x = base;
  bigint n = exp;

  while (n > 0) {
    if (n % 2 == 1) {
      result *= x;
    }
    x *= x;
    n = n / 2;
  }

  return result;
}

bigfloat radical(bigfloat const &radicand, bigint const &index,
                 bigfloat const &EPS) {
  if (radicand < 0 && index % 2 == 0) {
    throw std::invalid_argument("Negative radicand with even index");
  }
  if (index == 0) {
    throw std::invalid_argument("Index can not be zero!");
  }

  bigfloat x = radicand;
  bigfloat delta;

  do {
    bigfloat x_prev = x;
    x = ((index - 1) * x + radicand / pow(x, index - 1)) / index;
    delta = (x - x_prev).abs();
  } while (delta > EPS);

  return x;
}

bigfloat sqrt(bigfloat const &radicand, bigfloat const &EPS) {
  return radical(radicand, 2, EPS);
}
