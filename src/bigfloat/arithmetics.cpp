#include <utility>

#include "bigfloat.h"

void bigfloat::simplify() {
  if (numerator_ == 0) {
    denominator_ = 1;
    return;
  }
  if (numerator_ < 0) {
    numerator_.negate();
    denominator_.negate();
  }
  bigint divider = bigint::gcd(numerator_, denominator_.abs());
  if (divider == 1) {
    return;
  }
  numerator_ /= divider;
  denominator_ /= divider;
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
  numerator_ =
      numerator_ * other.denominator_ + other.numerator_ * denominator_;
  denominator_ *= other.denominator_;

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
  if (other == 0) {
    throw bigint::zero_division_exception();
  }
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

bigfloat bigfloat::reciprocal() const {
  bigfloat res(denominator_, numerator_);
  if (res.numerator_ < 0) {
    res.numerator_.negate();
    res.denominator_.negate();
  }
  return res;
}

bigfloat bigfloat::truncate() const { return {numerator_ / denominator_, 1}; }
