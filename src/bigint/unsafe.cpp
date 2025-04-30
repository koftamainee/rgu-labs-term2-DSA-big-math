#include <climits>
#include <cstring>
#include <exception>
#include <stdexcept>
#include <vector>

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

  // remove_leading_zeros();
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
  // adding_to += summand << shift;
  // return;

  size_t bit_shift = shift % (sizeof(int) * 8);
  size_t word_shift = shift / (sizeof(int) * 8);

  if (bit_shift != 0) {
    summand <<= bit_shift;
  }

  size_t summand_imaginary_size = word_shift + summand.size();
  size_t max_size = (summand_imaginary_size > adding_to.size())
                        ? summand_imaginary_size
                        : adding_to.size();
  if (adding_to.size() == summand_imaginary_size) {
    ++max_size;
  }

  auto *result = new int[max_size]();

  unsigned int extra_digit = 0;

  unsigned int (*loword_hiword_function_pointers[])(unsigned int) = {loword,
                                                                     hiword};
  int other_pos = 0;

  for (int i = 0; i < max_size; ++i) {
    if (i < word_shift) {
      result[i] = (i < adding_to.size()) ? adding_to[i] : 0;
      continue;
    }
    result[i] = 0;
    int this_digit = 0;
    int other_digit = 0;

    // std::cout << pos << ", " << i << std::endl;

    try {
      this_digit = adding_to[i];
    } catch (std::exception const &e) {
      this_digit = 0;
    }
    try {
      other_digit = summand[other_pos++];
    } catch (std::exception const &e) {
      other_digit = 0;
    }

#pragma unroll
    for (int j = 0; j < 2; ++j) {
      unsigned int this_half_digit =
          loword_hiword_function_pointers[j](this_digit);
      unsigned int other_half_digit =
          loword_hiword_function_pointers[j](other_digit);

      unsigned int digits_sum =
          this_half_digit + other_half_digit + extra_digit;
      extra_digit = (digits_sum >> SHIFT);
      unsigned int unsigned_result = (digits_sum & MASK) << (j * SHIFT);
      result[i] += *reinterpret_cast<int *>(&unsigned_result);
    }
  }

  // std::cout << "result: ";
  // for (int i = 0; i < max_size; ++i) {
  //   std::cout << result[i] << ", ";
  // }
  // std::cout << "\n";
  adding_to.move_from_array(result, max_size);
  // std::cout << "result: " << adding_to << std::endl;
}
