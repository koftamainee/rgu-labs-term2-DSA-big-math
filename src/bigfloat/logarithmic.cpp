#include <stdexcept>

#include "bigfloat.h"

bigfloat log2(bigfloat const &number, bigfloat const &EPS) {
  bigfloat ln2 = log(2, EPS);
  return log(number, EPS) / ln2;
}

bigfloat log(bigfloat const &number, bigfloat const &EPS) {
  if (number <= 0) {
    throw std::invalid_argument("logarithm of non-positive number");
  }
  bigfloat result = 0;
  bigfloat term = (number - 1) / (number + 1);
  bigfloat term_squared = term * term;
  bigfloat current_term = term;
  bigint n = 1;

  while (current_term.abs() > EPS) {
    result += current_term / n;
    current_term *= term_squared;
    n += 2;
  }
  return 2 * result;
}

bigfloat log10(bigfloat const &number, bigfloat const &EPS) {
  bigfloat ln10 = log(10, EPS);
  return log(number, EPS) / ln10;
}
