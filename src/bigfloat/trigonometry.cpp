#include "bigfloat.h"

bigfloat bigfloat::PI(bigfloat const &EPS) {
  static bigfloat pi = arctg(1, EPS) * 4;
  return pi;
}

bigfloat sin(bigfloat const &number, bigfloat const &EPS) {
  bigfloat res = 0;
  bigfloat term = number;
  bigfloat number_squared = number * number;
  bigint n = 1;

  while (term.abs() > EPS) {
    res += term;
    term *= -number_squared;
    ++n;
    term /= (2 * n - 1) * (2 * n - 2);
  }

  return res;
}

bigfloat cos(bigfloat const &number, bigfloat const &EPS) {
  bigfloat res = 0;
  bigfloat term = 1;
  bigfloat number_squared = number * number;
  bigint n = 0;

  while (term.abs() > EPS) {
    res += term;
    term *= -number_squared;
    ++n;
    term /= (2 * n - 1) * (2 * n);
  }

  return res;
}

bigfloat tg(bigfloat const &number, bigfloat const &EPS) {
  return sin(number, EPS) / cos(number, EPS);
}

bigfloat ctg(bigfloat const &number, bigfloat const &EPS) {
  return cos(number, EPS) / sin(number, EPS);
}

bigfloat sec(bigfloat const &number, bigfloat const &EPS) {
  return sin(number, EPS).reciprocal();
}

bigfloat cosec(bigfloat const &number, bigfloat const &EPS) {
  return cos(number, EPS).reciprocal();
}

bigfloat arcsin(bigfloat const &number, bigfloat const &EPS) {
  bigfloat result = number;
  bigfloat term = number;
  bigint n = 1;

  while (term.abs() > EPS) {
    term = term * number * number * (2 * n - 1) * (2 * n - 1) /
           (2 * n * (2 * n + 1));
    result += term;
    ++n;
  }
  return result;
}

bigfloat arccos(bigfloat const &number, bigfloat const &EPS) {
  return (bigfloat::PI(EPS) / 2) - arcsin(number, EPS);
}

bigfloat arctg(bigfloat const &number, bigfloat const &EPS) {
  bigfloat result = number;
  bigfloat term = number;
  bigint n = 1;

  while (term.abs() > EPS) {
    term = -term * number * number * (2 * n - 1) / (2 * n + 1);
    result += term;
    ++n;
  }
  return result;
}

bigfloat arcctg(bigfloat const &number, bigfloat const &EPS) {
  return (bigfloat::PI(EPS) / 2) - arctg(number, EPS);
}

bigfloat arcsec(bigfloat const &number, bigfloat const &EPS) {
  return arccos(number.reciprocal(), EPS);
}

bigfloat arccosec(bigfloat const &number, bigfloat const &EPS) {
  return arcsin(number.reciprocal(), EPS);
}
