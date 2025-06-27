#include "bigfloat.h"

bool operator==(bigfloat const &first, bigfloat const &second) {
  return first.numerator_ == second.numerator_ &&
         first.denominator_ == second.denominator_;
}

bool operator!=(bigfloat const &first, bigfloat const &second) {
  return !(first == second);
}

bool operator<(bigfloat const &first, bigfloat const &second) {
  if (first.denominator_ < 0 && second.denominator_ > 0) {
    return true;
  }
  if (first.denominator_ > 0 && second.denominator_ < 0) {
    return false;
  }
  bigint new_first_numerator = first.numerator_ * second.denominator_;
  bigint new_second_numerator = second.numerator_ * first.denominator_;
  return new_first_numerator < new_second_numerator;
}

bool operator<=(bigfloat const &first, bigfloat const &second) {
  return !(first > second);
}

bool operator>(bigfloat const &first, bigfloat const &second) {
  if (first.denominator_ < 0 && second.denominator_ > 0) {
    return false;
  }
  if (first.denominator_ > 0 && second.denominator_ < 0) {
    return true;
  }
  bigint new_first_numerator = first.numerator_ * second.denominator_;
  bigint new_second_numerator = second.numerator_ * first.denominator_;
  return new_first_numerator > new_second_numerator;
}

bool operator>=(bigfloat const &first, bigfloat const &second) {
  return !(first < second);
}
