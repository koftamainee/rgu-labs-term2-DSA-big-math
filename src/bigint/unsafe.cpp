#include <climits>
#include <cstring>

#include "bigint.h"

bigint &bigint::_raw_positive_increment() {
  auto const digits_count = size();

  for (int i = 0; i < digits_count - 1; ++i) {
    if (++((*this)[i]) != 0) {  // if not overflow
      remove_leading_zeros();
      return *this;
    }
  }

  if (++oldest_digit_ != INT_MIN) {
    remove_leading_zeros();
    return *this;
  }

  if (other_digits_ == nullptr) {
    other_digits_ = new int[2];
    other_digits_[0] = 2;
    other_digits_[1] = oldest_digit_;
    oldest_digit_ = 0;

    remove_leading_zeros();
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

  remove_leading_zeros();
  return *this;
}

bigint &bigint::_raw_positive_decrement() {
  if (sign() == 0) {
    oldest_digit_ = -1;
    return *this;
  }
  auto const digits_count = size();
  for (int i = 0; i < digits_count - 1; ++i) {
    if (--((*this)[i]) != -1) {
      remove_leading_zeros();
      return *this;
    }
  }

  if (--oldest_digit_ != INT_MAX) {
    remove_leading_zeros();
    return *this;
  }

  if (other_digits_ == nullptr) {
    other_digits_ = new int[2];
    other_digits_[0] = 2;
    other_digits_[1] = oldest_digit_;
    oldest_digit_ = -1;

    remove_leading_zeros();
    return *this;
  }

  int *new_array = new int[digits_count + 1];
  memcpy(new_array, other_digits_, sizeof(int) * digits_count);
  delete[] other_digits_;
  other_digits_ = new_array;

  (*this)[digits_count] = oldest_digit_;
  --(*this).other_digits_[0];
  oldest_digit_ = 0;

  remove_leading_zeros();
  return *this;
}

bigint &bigint::_raw_negative_increment() {
  _raw_positive_increment();
  return *this;
}
bigint &bigint::_raw_negative_decrement() {
  _raw_positive_decrement();
  return *this;
}
