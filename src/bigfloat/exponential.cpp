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

bigfloat radical(const bigfloat &radicand, const bigint &index,
                 const bigfloat &EPS) {
  if (index == 0) {
    throw std::invalid_argument("Index cannot be zero!");
  }
  if (radicand < 0 && (index % 2 == 0)) {
    throw std::invalid_argument("Negative radicand with even index");
  }

  bigfloat approx = 1;
  while (pow(approx, index) < radicand.abs()) {
    approx *= 2;
  }
  bigfloat x = (radicand < 0) ? -approx : approx;

  bigfloat delta;

  do {
    bigfloat x_prev = x;

    bigfloat x_to_power = 1;
    for (bigint i = 0; i < index - 1; ++i) {
      x_to_power *= x;
    }

    x = ((index - 1) * x + radicand / x_to_power) / index;

    delta = (x - x_prev).abs();
  } while (delta > EPS);

  return x;
}

bigfloat sqrt(bigfloat const &radicand, bigfloat const &EPS) {
  return radical(radicand, 2, EPS);
}
