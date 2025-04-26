#include "bigfloat.h"

bigint bigfloat::gcd(bigint a, bigint b) {
  // Take absolute values
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

void bigfloat::simplify() {
  bigint divider = gcd(numerator_, denominator_);
  if (divider == 0) {
    return;
  }
  numerator_ /= divider;
  denominator_ /= divider;

  if (denominator_ < 0) {
    numerator_ = -numerator_;
    denominator_ = -denominator_;
  }
}
bigfloat bigfloat::operator-() const {
  bigfloat negative = *this;
  return negative.negate();
}

bigfloat &bigfloat::negate() {
  denominator_.negate();
  return *this;
}

bigfloat &bigfloat::operator+=(bigfloat const &other) & {
  *this *= other.denominator_;
  bigint new_other_numerator = other.numerator_ * denominator_;
  numerator_ += new_other_numerator;

  simplify();
  return *this;
}

bigfloat operator+(bigfloat const &first, bigfloat const &second) {
  bigfloat temp = first;
  return temp += second;
}

bigfloat &bigfloat::operator-=(bigfloat const &other) & {
  return *this += -other;
}

bigfloat operator-(bigfloat const &first, bigfloat const &second) {
  return first + -second;
}

bigfloat &bigfloat::operator*=(bigfloat const &other) & {
  numerator_ *= other.numerator_;
  denominator_ *= other.denominator_;
  simplify();
  return *this;
}

bigfloat operator*(bigfloat const &first, bigfloat const &second) {
  bigfloat temp = first;
  return temp *= second;
}

bigfloat &bigfloat::operator/=(bigfloat const &other) & {
  numerator_ *= other.denominator_;
  denominator_ *= other.numerator_;
  simplify();
  return *this;
}

bigfloat operator/(bigfloat const &first, bigfloat const &second) {
  bigfloat temp = first;
  return temp /= second;
}

bigfloat bigfloat::abs() const { return denominator_ < 0 ? -*this : *this; }
