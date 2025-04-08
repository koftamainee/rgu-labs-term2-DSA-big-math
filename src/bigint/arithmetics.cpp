#include <climits>
#include <cstring>
#include <iostream>

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
  return (sign() == 1) ? ++(bit_inverse()) : (--(*this)).bit_inverse();
}

bigint operator-(bigint const &first, bigint const &second) {
  return first + (-second);
}

bigint &bigint::operator++() & {
  if (sign() == -1) {
    return (--negate()).negate();
  }

  auto const digits_count = size();

  for (int i = 0; i < digits_count - 1; ++i) {
    if (++((*this)[i]) != 0) {  // if not overflow
      return *this;
    }
  }

  if (++oldest_digit_ != INT_MIN) {
    return *this;
  }

  if (other_digits_ == nullptr) {
    other_digits_ = new int[2];
    other_digits_[0] = 2;
    other_digits_[1] = oldest_digit_;
    oldest_digit_ = 0;

    return *this;
  }

  int *new_array = new int[digits_count + 1];
  memcpy(new_array, other_digits_, sizeof(int) * size());
  delete[] other_digits_;
  other_digits_ = new_array;
  new_array = nullptr;

  (*this)[digits_count] = oldest_digit_;
  ++(*this).other_digits_[0];
  oldest_digit_ = 0;
  return *this;
}

bigint const bigint::operator++(int) & {
  auto const copy = *this;
  ++(*this);
  return copy;
}

bigint &bigint::operator--() & {
  if (sign() == -1) {
    return (++negate()).negate();
  }
  if (sign() == 0) {
    oldest_digit_ = -1;
    return *this;
  }
  auto const digits_count = size();
  for (int i = 0; i < digits_count - 1; ++i) {
    if (--((*this)[i]) != -1) {
      return *this;
    }
  }

  if (--oldest_digit_ != INT_MAX) {
    return *this;
  }

  if (other_digits_ == nullptr) {
    other_digits_ = new int[2];
    other_digits_[0] = 2;
    other_digits_[1] = oldest_digit_;
    oldest_digit_ = -1;
    return *this;
  }

  int *new_array = new int[digits_count + 1];
  memcpy(new_array, other_digits_, sizeof(int) * digits_count);
  delete[] other_digits_;
  other_digits_ = new_array;

  (*this)[digits_count] = oldest_digit_;
  --(*this).other_digits_[0];
  oldest_digit_ = 0;
  return *this;
}

bigint const bigint::operator--(int) & {
  auto const copy = *this;
  --(*this);
  return copy;
}

bigint &bigint::operator+=(bigint const &other) & {
  unsigned int (*loword_hiword_function_pointers[])(unsigned int) = {loword,
                                                                     hiword};
  unsigned int max_size = max(size(), other.size());
  int *result = new int[max_size];
  unsigned int extra_digit = 0;

  for (int i = 0; i < max_size; ++i) {
    result[i] = 0;

    auto this_digit = static_cast<bigint const *>(this)->operator[](i);
    auto other_digit = other[i];

#pragma unroll
    for (int j = 0; j < 2; ++j) {
      auto this_half_digit = loword_hiword_function_pointers[j](this_digit);
      auto other_half_digit = loword_hiword_function_pointers[j](other_digit);

      auto digits_sum = this_half_digit + other_half_digit + extra_digit;
      extra_digit = digits_sum >> SHIFT;
      result[i] += static_cast<int>((digits_sum & MASK) << (j * SHIFT));
    }
  }

  // TODO something

  return *this;
}

bigint operator+(bigint const &first, bigint const &second) {
  bigint temp = first;
  return temp += second;
}

bigint &bigint::operator-=(bigint const &other) & { return *this += (-other); }

bigint &bigint::operator*=(bigint const &other) & {}

bigint operator*(bigint const &first, bigint const &second) {}

bigint &bigint::operator/=(bigint const &other) & {}

bigint operator/(bigint const &first, bigint const &second) {}

bigint &bigint::operator%=(bigint const &other) & {}

bigint operator%(bigint const &first, bigint const &second) {}
