#include "bigfloat.h"

bigint bigfloat::gcd(bigint first,
                     bigint second) {  // very expensive.. mb rewrite later
  while (second != 0) {
    bigint temp = second;
    second = first % second;
    first = temp;
  }

  return first;
}

void bigfloat::simplify() {
  bigint divider = gcd(numerator_, demonimator_);
  numerator_ /= divider;
  demonimator_ /= divider;
}

bigfloat bigfloat::operator-() const {
  bigfloat negative = *this;
  return negative.negate();
}

bigfloat &bigfloat::negate() {
  demonimator_.negate();
  return *this;
}

bigfloat &bigfloat::operator+=(bigfloat const &other) & {
  *this *= other.demonimator_;
  bigint new_other_numerator = other.numerator_ * demonimator_;
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
  demonimator_ *= other.demonimator_;
  simplify();
  return *this;
}

bigfloat operator*(bigfloat const &first, bigfloat const &second) {
  bigfloat temp = first;
  return temp *= second;
}

bigfloat &bigfloat::operator/=(bigfloat const &other) & {
  numerator_ *= other.demonimator_;
  demonimator_ *= other.numerator_;
  simplify();
  return *this;
}

bigfloat operator/(bigfloat const &first, bigfloat const &second) {
  bigfloat temp = first;
  return temp /= second;
}

bigfloat bigfloat::abs() const { return demonimator_ < 0 ? -*this : *this; }
