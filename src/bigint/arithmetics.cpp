#include <climits>
#include <cstdint>
#include <cstring>

#include "bigint.h"

bigint bigint::operator-() const {
  bigint negative = *this;
  return negative.negate();
}

bigint bigint::abs() const { return sign() < 0 ? -*this : *this; }

bigint &bigint::negate() & {
  if (sign() == 0) {
    return *this;
  }
  if (sign() == 1) {
    bit_inverse();
    _raw_negative_increment();
    return *this;
  }

  _raw_positive_decrement();  // TODO: rewrite _raw_negative_decrement without
                              // +=
  bit_inverse();
  return *this;
}

bigint &bigint::operator++() & {
  if (sign() == -1) {
    return _raw_negative_increment();
  }

  return _raw_positive_increment();
}

bigint const bigint::operator++(int) & {
  auto const copy = *this;
  ++(*this);
  return copy;
}

bigint &bigint::operator--() & {
  if (sign() == -1) {
    return _raw_negative_decrement();
  }

  return _raw_positive_decrement();
}

bigint const bigint::operator--(int) & {
  auto const copy = *this;
  --(*this);
  return copy;
}

bigint &bigint::operator+=(bigint const &other) & {
  int this_sign = sign();
  int other_sign = other.sign();

  if (this_sign == 0) {
    return *this = other;
  }

  if (other_sign == 0) {
    return *this;
  }

  unsigned int this_size = size();
  unsigned int other_size = other.size();
  unsigned int max_size = (this_size > other_size ? this_size : other_size) + 1;

  int *result = new int[max_size];
  uint64_t carry = 0;

  for (unsigned int i = 0; i < max_size; ++i) {
    uint32_t this_digit =
        (i < this_size) ? static_cast<uint32_t>((*this)[i]) : 0;
    uint32_t other_digit =
        (i < other_size) ? static_cast<uint32_t>(other[i]) : 0;

    uint64_t sum = static_cast<uint64_t>(this_digit) + other_digit + carry;
    carry = sum >> 32;
    result[i] = static_cast<int>(sum & 0xFFFFFFFF);
  }

  move_from_array(result, max_size);
  return *this;
}
bigint operator+(bigint const &first, bigint const &second) {
  bigint temp = first;
  return temp += second;
}

bigint &bigint::operator-=(bigint const &other) & { return *this += (-other); }

bigint operator-(bigint const &first, bigint const &second) {
  return first + (-second);
}

bigint &bigint::operator*=(bigint const &other) & {
  if (this->sign() == 0 || other.sign() == 0) {
    *this = 0;
    return *this;
  }
  if (other == 1) {
    return *this;
  }
  if (*this == 1) {
    return *this = other;
  }
  if (other == -1) {
    return this->negate();
  }
  if (*this == -1) {
    return *this = -other;
  }

  if (this->sign() == -1 && other.sign() == -1) {
    return this->negate() *= -other;
  }

  if (other.sign() == -1) {
    return (*this *= -other).negate();
  }
  if (this->sign() == -1) {
    return (this->negate() *= other).negate();
  }

  return multiply(other);
}

bigint &bigint::multiply(bigint const &other) {
  if (size() >= KARATSUBA_THRESHOLD && other.size() >= KARATSUBA_THRESHOLD) {
    return karatsuba_multiply(other);
  }
  return scholarbook_multiply(other);
}

bigint operator*(bigint const &first, bigint const &second) {
  bigint copy = first;
  return copy *= second;
}

bigint &bigint::operator/=(bigint const &other) & {
  return *this = std::move(division(*this, other).quotient());
}

bigint operator/(bigint const &first, bigint const &second) {
  return bigint::division(first, second).quotient();
}

bigint &bigint::operator%=(bigint const &other) & {
  return *this = std::move(division(*this, other).remainder());
}

bigint operator%(bigint const &first, bigint const &second) {
  return bigint::division(first, second).remainder();
}
