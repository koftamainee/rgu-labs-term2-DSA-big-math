#include "bigint.h"

bigint bigint::operator~() const {
  auto temp = *this;
  return temp.bit_inverse();
}

bigint &bigint::bit_inverse() & {
  oldest_digit_ = ~oldest_digit_;
  if (other_digits_ == nullptr) {
    return *this;
  }
  for (int i = 1; i < size() - 1; ++i) {
    other_digits_[i] = ~other_digits_[i];
  }

  return *this;
}

bigint &bigint::operator&=(bigint const &other) & {}

bigint operator&(bigint const &first, bigint const &second) {}

bigint &bigint::operator|=(bigint const &other) & {}

bigint operator|(bigint const &first, bigint const &second) {}

bigint &bigint::operator^=(bigint const &other) & {}

bigint operator^(bigint const &first, bigint const &second) {}

bigint &bigint::operator<<=(size_t index) & {}

bigint bigint::operator<<(size_t index) {}

bigint &bigint::operator>>=(size_t index) & {}

bigint bigint::operator>>(size_t index) {}
