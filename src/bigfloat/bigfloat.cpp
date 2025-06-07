#include "bigfloat.h"

#include <stdexcept>

const bigfloat bigfloat::DEFAULT_EPS = bigfloat(bigint(1), bigint(1000000));

std::map<bigfloat, bigfloat> bigfloat::pi_cache_;
std::vector<bigfloat> bigfloat::bernoulli_cache_ = {1, bigfloat(-1, 2)};

bigfloat::bigfloat() {
  numerator_ = 0;
  denominator_ = 1;
}

bigfloat::bigfloat(int other) : bigfloat(bigint(other)) {}

bigfloat::bigfloat(bigint const &numerator, bigint const &denominator) {
  if (denominator == 0) {
    throw std::invalid_argument("Demonimator can not be 0");
  }
  if (numerator >= 0 && denominator >= 0) {
    numerator_ = numerator;
    denominator_ = denominator;
  } else if (numerator < 0 || denominator < 0) {
    numerator_ = -numerator;
    denominator_ = -denominator;
  } else {
    numerator_ = numerator.abs();
    denominator_ = denominator < 0 ? denominator : -denominator;
  }
  simplify();
}

bigfloat::bigfloat(bigint const &other)
    : numerator_(other.abs()), denominator_(other < 0 ? -1 : 1) {}
