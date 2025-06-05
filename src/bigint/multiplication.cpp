
#include "bigint.h"

void bigint::accumulate_multiplication(
    bigint &result, unsigned int *words_multiplication_result_digits,
    unsigned int a, unsigned int b, size_t position_shift) {
  if (a == 0 || b == 0) {
    return;
  }
  unsigned int product = a * b;
  words_multiplication_result_digits[0] = product;

  bigint temp(reinterpret_cast<int *>(words_multiplication_result_digits), 2);

  _add_with_shift(result, temp, position_shift);
}

bigint &bigint::scholarbook_multiply(bigint const &other) & {
  unsigned int words_multiplication_result_digits[2] = {0};
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

      accumulate_multiplication(
          result, words_multiplication_result_digits, this_digit_loword,
          other_digit_loword,
          (static_cast<long long>(i + j)) * sizeof(int) * 8);

      accumulate_multiplication(result, words_multiplication_result_digits,
                                this_digit_loword, other_digit_hiword,
                                ((i + j) * (sizeof(int) * 8)) + SHIFT);

      accumulate_multiplication(result, words_multiplication_result_digits,
                                this_digit_hiword, other_digit_loword,
                                ((i + j) * sizeof(int) * 8) + SHIFT);

      accumulate_multiplication(
          result, words_multiplication_result_digits, this_digit_hiword,
          other_digit_hiword, static_cast<size_t>(i + j + 1) * sizeof(int) * 8);
    }
  }
  return *this = std::move(result);
}

bigint &bigint::karatsuba_multiply(bigint const &other) & {
  auto const this_size = this->size();
  auto const other_size = other.size();

  size_t const m = (std::max(this_size, other_size)) / 2;

  bigint const high1 = this->get_upper(m);
  bigint const low1 = this->get_lower(m);
  bigint const high2 = other.get_upper(m);
  bigint const low2 = other.get_lower(m);

  bigint z0 = low1 * low2;
  bigint z2 = high1 * high2;
  bigint z1 = (low1 + high1) * (low2 + high2);

  // std::cout << z1 << " + " << -z2 << " = ";
  z1 -= z2;
  // std::cout << z1 << std::endl;
  // std::cout << z1 << " + " << -z0 << " = ";
  z1 -= z0;
  // std::cout << z1 << std::endl;

  bigint result = std::move(z0);
  _add_with_word_shift(result, z1, m);
  _add_with_word_shift(result, z2, 2 * m);

  return *this = std::move(result);
}
