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

bigint &bigint::operator&=(bigint const &other) & {
  auto const first_size = size();

  for (int i = 0; i < first_size; ++i) {
    unsigned int const other_digit = other[i];
    auto const other_digit_int = *reinterpret_cast<int const *>(&other_digit);
    this->operator[](i) &= other_digit_int;
  }
  return *this;
}

bigint operator&(bigint const &first, bigint const &second) {
  bigint copy = first;
  return copy &= second;
}

bigint &bigint::operator|=(bigint const &other) & {
  auto const first_size = size();

  for (int i = 0; i < first_size; ++i) {
    unsigned int const other_digit = other[i];
    auto const other_digit_int = *reinterpret_cast<int const *>(&other_digit);
    this->operator[](i) |= other_digit_int;
  }
  return *this;
}

bigint operator|(bigint const &first, bigint const &second) {
  bigint copy = first;
  return copy |= second;
}

bigint &bigint::operator^=(bigint const &other) & {
  auto const first_size = size();

  for (int i = 0; i < first_size; ++i) {
    unsigned int const other_digit = other[i];
    auto const other_digit_int = *reinterpret_cast<int const *>(&other_digit);
    this->operator[](i) ^= other_digit_int;
  }
  return *this;
}

bigint operator^(bigint const &first, bigint const &second) {
  bigint copy = first;
  return copy ^= second;
}

bigint &bigint::operator<<=(size_t index) & {}

bigint bigint::operator<<(size_t index) {
  bigint copy = *this;
  return copy <<= index;
}

bigint &bigint::operator>>=(size_t index) & {}

bigint bigint::operator>>(size_t index) {
  bigint copy = *this;
  return copy >>= index;
}
