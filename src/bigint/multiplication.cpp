#include "bigint.h"

void bigint::accumulate_multiplication(
    bigint &result, unsigned int words_multiplication_result_digits[3],
    unsigned int a, unsigned int b, size_t position_shift) {
  auto product =
      static_cast<unsigned long long>(a) * static_cast<unsigned long long>(b);
  words_multiplication_result_digits[0] =
      static_cast<unsigned int>(product & 0xFFFFFFFF);
  words_multiplication_result_digits[1] =
      static_cast<unsigned int>(product >> 32);

  bigint temp(reinterpret_cast<int *>(words_multiplication_result_digits), 3);
  _add_with_shift(result, temp, position_shift);
}

bigint &bigint::scholarbook_multiply(bigint const &other) & {
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
                                (static_cast<long long>(i + j)) * 32);

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

bigint &bigint::karatsuba_multiply(bigint const &other) {
  const size_t this_size = this->size();
  const size_t other_size = other.size();

  if (this_size < KARATSUBA_THRESHOLD || other_size < KARATSUBA_THRESHOLD) {
    return scholarbook_multiply(other);
  }

  const size_t m = (std::min(this_size, other_size) + 1) / 2;

  bigint high1;
  bigint low1;
  bigint high2;
  bigint low2;

  high1 = std::move(this->get_upper(m));
  low1 = std::move(this->get_lower(m));

  high2 = std::move(other.get_upper(m));
  low2 = std::move(other.get_lower(m));

  bigint z1 = std::move((low1 + high1).karatsuba_multiply(low2 + high2));

  // z0 = low1
  low1.karatsuba_multiply(low2);
  // z2 = high1
  high1.karatsuba_multiply(high2);

  z1 -= low1;
  z1 -= high1;

  _add_with_shift(*this, high1, m << 1);
  _add_with_shift(*this, z1, m);
  *this += low1;

  return *this;
}
