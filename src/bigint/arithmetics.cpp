#include <climits>
#include <cstddef>
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
  return (sign() == 1) ? (bit_inverse() += 1) : ((*this) += -1).bit_inverse();
}

bigint &bigint::operator++() & {
  if (sign() == -1) {
    return *this += 1;
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
    return *this += -1;
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
  int result_sign = 0;
  int this_sign = sign();
  int other_sign = other.sign();

  if (this_sign == other_sign) {
    result_sign = this_sign;
  } else {
    if (this_sign == -1) {
      result_sign = ((*this).abs() > other) ? -1 : 1;
    } else {
      result_sign = ((*this) < other.abs()) ? -1 : 1;
    }
  }

  unsigned int max_size = max(size(), other.size()) + 1;
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

      if (i == max_size - 1) {
        if (this_digit == 0 && other_digit == 0 && extra_digit != 0) {
          result[i] = result_sign;
          break;
        }
      }

      unsigned int digits_sum =
          this_half_digit + other_half_digit + extra_digit;
      extra_digit = (digits_sum >> SHIFT);
      result[i] += static_cast<int>((digits_sum & MASK) << (j * SHIFT));
    }
  }

  if (result_sign == -1 && result[max_size - 1] == 0) {
    --max_size;
  }

  if ((this_sign == -1 || other_sign == -1) && result_sign == 1 &&
      result[max_size - 1] == 1) {
    --max_size;
  }

  from_array(result, max_size);
  delete[] result;

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

void bigint::accumulate_multiplication(
    bigint &result, unsigned int words_multiplication_result_digits[3],
    unsigned int a, unsigned int b, size_t position_shift) {
  auto product = static_cast<uint64_t>(a) * static_cast<unsigned long long>(b);
  words_multiplication_result_digits[0] =
      static_cast<uint32_t>(product & 0xFFFFFFFF);
  words_multiplication_result_digits[1] = static_cast<uint32_t>(product >> 32);

  bigint temp(reinterpret_cast<int *>(words_multiplication_result_digits), 3);
  temp <<= position_shift;

  result += temp;
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

  unsigned int words_multiplication_result_digits[3] = {0};
  int digit = 0;
  unsigned int words_multiplication_result_digit = 0;
  auto this_size = size();
  auto other_size = other.size();
  bigint const *first = this;

  bigint result = 0;

  for (int i = 0; i < this_size; ++i) {
    unsigned int this_digit = first->operator[](i);
    unsigned int this_digit_loword = loword(this_digit);
    unsigned int this_digit_hiword = hiword(this_digit);

    for (int j = 0; j < other_size; ++j) {
      unsigned int other_digit = other[j];
      unsigned int other_digit_loword = loword(other_digit);
      unsigned int other_digit_hiword = hiword(other_digit);

      accumulate_multiplication(result, words_multiplication_result_digits,
                                this_digit_loword, other_digit_loword,
                                (static_cast<long>(i + j)) * 32);

      accumulate_multiplication(result, words_multiplication_result_digits,
                                this_digit_loword, other_digit_hiword,
                                ((i + j) * 32) + 16);

      accumulate_multiplication(result, words_multiplication_result_digits,
                                this_digit_hiword, other_digit_loword,
                                ((i + j) * 32) + 16);

      accumulate_multiplication(result, words_multiplication_result_digits,
                                this_digit_hiword, other_digit_hiword,
                                static_cast<size_t>(i + j + 1) * 32);
    }
  }
  return *this = std::move(result);
}

bigint operator*(bigint const &first, bigint const &second) {
  bigint copy = first;
  return copy *= second;
}

division_result division(bigint const &first, bigint const &second) {}

bigint &bigint::operator/=(bigint const &other) & {}

bigint operator/(bigint const &first, bigint const &second) {}

bigint &bigint::operator%=(bigint const &other) & {}

bigint operator%(bigint const &first, bigint const &second) {}
