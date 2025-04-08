#include "bigfloat.h"

#include <optional>
#include <stdexcept>

bigfloat::bigfloat() {
  numerator_ = 0;
  denominator_ = 1;
}

bigfloat::bigfloat(bigint const &numerator, bigint const &demonimator) {
  if (demonimator == 0) {
    throw std::invalid_argument("Demonimator can not be 0");
  }
  if (numerator >= 0 && demonimator >= 0) {
    numerator_ = numerator;
    denominator_ = demonimator;
  } else if (numerator < 0 || demonimator < 0) {
    numerator_ = -numerator;
    denominator_ = -demonimator;
  } else {
    numerator_ = numerator.abs();
    denominator_ = demonimator < 0 ? demonimator : -demonimator;
  }
  simplify();
}

bigfloat::bigfloat(bigint const &other)
    : numerator_(other.abs()), denominator_(other < 0 ? -1 : 1) {}

bigfloat::bigfloat(double num)
    : numerator_(std::abs(static_cast<int>(num))),
      denominator_(num < 0 ? -1 : 1) {}

std::optional<double> bigfloat::to_double() noexcept {
  auto int_numerator = numerator_.to_int();
  auto int_demonimator = denominator_.to_int();
  if (!int_numerator || !int_demonimator) {
    return std::nullopt;
  }
  return *int_numerator / *int_demonimator;
}
