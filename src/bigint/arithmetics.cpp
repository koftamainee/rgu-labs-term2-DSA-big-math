#include <climits>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <exception>

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
  unsigned int (*loword_hiword_function_pointers[])(unsigned int) = {loword,
                                                                     hiword};

  int result_sign = 0;
  int this_sign = sign();
  int other_sign = other.sign();
  if (this_sign == 0) {
    return *this = other;
  }
  if (other_sign == 0) {
    return *this;
  }

  if (this_sign == other_sign) {
    result_sign = this_sign;
  } else {
    if (this_sign == -1) {
      result_sign = ((*this).abs() > other) ? -1 : 1;
    } else {
      result_sign = ((*this) < other.abs()) ? -1 : 1;
    }
  }

  if (this_sign != other_sign && this->abs() == other.abs()) {
    return *this = 0;
  }

  unsigned int max_size = max(size(), other.size()) + 1;
  int *result = new int[max_size];
  unsigned int extra_digit = 0;

  for (int i = 0; i < max_size; ++i) {
    result[i] = 0;

    int this_digit = 0;
    int other_digit = 0;

    try {
      this_digit = this->operator[](i);
    } catch (std::exception const &e) {
      this_digit = 0;
    }
    try {
      other_digit = const_cast<bigint &>(other)[i];
    } catch (std::exception const &e) {
      other_digit = 0;
    }
#pragma unroll
    for (int j = 0; j < 2; ++j) {
      unsigned int this_half_digit =
          loword_hiword_function_pointers[j](this_digit);
      unsigned int other_half_digit =
          loword_hiword_function_pointers[j](other_digit);

      if (i == max_size - 1) {
        if (this_digit == 0 && other_digit == 0 && extra_digit != 0) {
          result[i] = result_sign;
          break;
        }
      }

      unsigned int digits_sum =
          this_half_digit + other_half_digit + extra_digit;
      extra_digit = (digits_sum >> SHIFT);
      unsigned int unsigned_result = (digits_sum & MASK) << (j * SHIFT);
      result[i] += *reinterpret_cast<int *>(&unsigned_result);
    }

    unsigned int next_this_digit =
        static_cast<bigint const *>(this)->operator[](i + 1);

    unsigned int next_other_digit = other[i + 1];

    bool signs_differ = (this_sign != other_sign);
    bool one_of_the_digits_negative = (this_digit < 0 && other_digit < 0);
    bool next_digits_zero = (next_other_digit == 0 || next_this_digit == 0);

    if ((signs_differ && one_of_the_digits_negative && next_digits_zero)) {
      extra_digit = 0;
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
  auto product =
      static_cast<unsigned long long>(a) * static_cast<unsigned long long>(b);
  words_multiplication_result_digits[0] =
      static_cast<unsigned int>(product & 0xFFFFFFFF);
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
