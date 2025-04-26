#include "bigfloat.h"

bigfloat bigfloat::PI(bigfloat const &EPS) { return 4 * arctg(1, EPS); }

bigfloat sin(bigfloat const &number, bigfloat const &EPS) {
  bigfloat result = 0;
  bigfloat term = number;
  bigint n = 1;
  while (term.abs() > EPS) {
    result += term;
    term = -term * number * number / ((2 * n) * (2 * n + 1));
    ++n;
  }

  return result;
}

bigfloat cos(bigfloat const &number, bigfloat const &EPS) {
  bigfloat result = 0;
  bigfloat term = 1;
  bigint n = 1;
  while (term.abs() > EPS) {
    result += term;
    term = -term * number * number / (n * (n - 1));
  }

  return result;
}

bigfloat tg(bigfloat const &number, bigfloat const &EPS) {
  return sin(number, EPS) / cos(number, EPS);
}

bigfloat ctg(bigfloat const &number, bigfloat const &EPS) {
  return cos(number, EPS) / sin(number, EPS);
}

bigfloat sec(bigfloat const &number, bigfloat const &EPS) {
  return 1 / sin(number, EPS);
}

bigfloat cosec(bigfloat const &number, bigfloat const &EPS) {
  return 1 / cos(number, EPS);
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
  return (bigfloat::PI(EPS) * 0.5) - arcsin(number, EPS);
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
  return arccos(1 / number, EPS);
}

bigfloat arccosec(bigfloat const &number, bigfloat const &EPS) {
  return arcsin(1 / number, EPS);
}
