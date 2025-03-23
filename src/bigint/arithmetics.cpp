#include "bigint.h"

bigint bigint::operator-() const {
  bigint negative = *this;
  return negative.negate();
}

bigint bigint::abs() const { return sign() < 0 ? -*this : *this; }

bigint &bigint::negate() & {}

bigint &bigint::operator++() & {}

bigint const bigint::operator++(int) & {}

bigint &bigint::operator--() & {}

bigint const bigint::operator--(int) & {}

bigint &bigint::operator+=(bigint const &other) & {
  unsigned int (*loword_hiword_function_pointers[])(unsigned int) = {loword,
                                                                     hiword};
  unsigned int max_size = max(size(), other.size());
  int *result = new int[max_size];
  unsigned int extra_digit = 0;

  for (int i = 0; i < max_size; ++i) {
    result[i] = 0;

    auto this_digit = this->operator[](i);
    auto other_digit = other[i];

#pragma unroll
    for (int j = 0; j < 2; ++j) {  // 2 iterations
      auto this_half_digit = loword_hiword_function_pointers[j](this_digit);
      auto other_half_digit = loword_hiword_function_pointers[j](other_digit);

      auto digits_sum = this_half_digit + other_half_digit + extra_digit;
      extra_digit = digits_sum >> SHIFT;
      result[i] += (digits_sum & MASK) << (j * SHIFT);
    }
  }

  // TODO something

  return *this;
}

bigint operator+(bigint const &first, bigint const &second) {}

bigint &bigint::operator-=(bigint const &other) & {}

bigint operator-(bigint const &first, bigint const &second) {}

bigint &bigint::operator*=(bigint const &other) & {}

bigint operator*(bigint const &first, bigint const &second) {}

bigint &bigint::operator/=(bigint const &other) & {}

bigint operator/(bigint const &first, bigint const &second) {}

bigint &bigint::operator%=(bigint const &other) & {}

bigint operator%(bigint const &first, bigint const &second) {}
