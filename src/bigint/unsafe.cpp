#include <climits>
#include <cstring>

#include "bigint.h"

bigint &bigint::_raw_positive_increment() {
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
  std::memcpy(new_array, other_digits_, sizeof(int) * size());
  delete[] other_digits_;
  other_digits_ = new_array;
  new_array = nullptr;

  (*this)[digits_count] = oldest_digit_;
  ++(*this).other_digits_[0];  // size++
  oldest_digit_ = 0;

  remove_leading_zeros();
  return *this;
}

bigint &bigint::_raw_positive_decrement() {
  if (sign() == 0) {
    oldest_digit_ = -1;
    remove_leading_zeros();
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

  this->other_digits_[digits_count] = oldest_digit_;
  ++(*this).other_digits_[0];
  oldest_digit_ = 0;

  remove_leading_zeros();
  return *this;
}

bigint &bigint::_raw_negative_increment() {
  // throw std::runtime_error(
  //     "_raw_negative_increment is not implemented");  // TODO
  // _raw_positive_increment();
  // return *this;
  return *this += 1;
}
bigint &bigint::_raw_negative_decrement() {
  // throw std::runtime_error(
  //     "_raw_negative_decrement is not implemented");  // TODO
  // _raw_positive_decrement();
  // return *this;
  return *this += -1;
}

void bigint::_add_with_shift(bigint &adding_to, bigint &summand, size_t shift) {
  if (summand == 0) {
    return;
  }

  if (adding_to == 0) {
    adding_to = std::move(summand << shift);
    return;
  }

  if (shift == 0) {
    adding_to += summand;
    return;
  }

  constexpr size_t bits_per_word = sizeof(int) << 3;
  size_t bit_shift = shift % bits_per_word;
  size_t word_shift = shift / bits_per_word;

  if (bit_shift != 0) {
    summand <<= bit_shift;
  }

  _add_with_word_shift(adding_to, summand, word_shift);
}

void bigint::_add_with_word_shift(bigint &adding_to, bigint &summand,
                                  size_t word_shift) {
  size_t adding_to_size = adding_to.size();
  size_t summand_size = summand.size();
  size_t total_summand_size = word_shift + summand_size;

  size_t max_size = (total_summand_size > adding_to_size) ? total_summand_size
                                                          : adding_to_size;
  if (adding_to_size == total_summand_size) {
    ++max_size;
  }

  int *result = new int[max_size];

  unsigned int extra_digit = 0;
  int summand_pos = 0;

  for (int i = 0; i < word_shift; ++i) {
    result[i] = (i < adding_to.size()) ? adding_to[i] : 0;
  }

  for (int i = static_cast<int>(word_shift); i < max_size; ++i) {
    int this_digit = (i < adding_to_size) ? adding_to[i] : 0;
    int other_digit = (summand_pos < summand_size) ? summand[summand_pos++] : 0;

    unsigned int this_low = loword(this_digit);
    unsigned int this_high = hiword(this_digit);
    unsigned int other_low = loword(other_digit);
    unsigned int other_high = hiword(other_digit);

    unsigned int sum_low = this_low + other_low + extra_digit;
    extra_digit = sum_low >> SHIFT;
    unsigned int result_low = sum_low & MASK;

    unsigned int sum_high = this_high + other_high + extra_digit;
    extra_digit = sum_high >> SHIFT;
    unsigned int result_high = sum_high & MASK;

    unsigned int combined = (result_high << SHIFT) | result_low;
    result[i] = *reinterpret_cast<int *>(&combined);
  }

  adding_to.move_from_array(result, max_size);
}
