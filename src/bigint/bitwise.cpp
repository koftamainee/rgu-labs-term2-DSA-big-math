#include <climits>
#include <cstring>

#include "bigint.h"

bigint bigint::operator~() const {
  auto temp = *this;
  return temp.bit_inverse();
}

bigint &bigint::bit_inverse() & {
  for (int i = 0; i < size(); ++i) {
    this->operator[](i) = ~this->operator[](i);
  }

  return *this;
}

bigint &bigint::operator&=(bigint const &other) & {
  auto const first_size = size();

  for (int i = 0; i < first_size; ++i) {
    unsigned int const other_digit = other[i];
    auto const other_digit_int = *reinterpret_cast<int const *>(&other_digit);
    this->operator[](i) &= other_digit_int;
  }
  return *this;
}

bigint operator&(bigint const &first, bigint const &second) {
  bigint copy = first;
  return copy &= second;
}

bigint &bigint::operator|=(bigint const &other) & {
  auto const first_size = size();

  for (int i = 0; i < first_size; ++i) {
    unsigned int const other_digit = other[i];
    auto const other_digit_int = *reinterpret_cast<int const *>(&other_digit);
    this->operator[](i) |= other_digit_int;
  }
  return *this;
}

bigint operator|(bigint const &first, bigint const &second) {
  bigint copy = first;
  return copy |= second;
}

bigint &bigint::operator^=(bigint const &other) & {
  auto const first_size = size();

  for (int i = 0; i < first_size; ++i) {
    unsigned int const other_digit = other[i];
    auto const other_digit_int = *reinterpret_cast<int const *>(&other_digit);
    this->operator[](i) ^= other_digit_int;
  }
  return *this;
}

bigint operator^(bigint const &first, bigint const &second) {
  bigint copy = first;
  return copy ^= second;
}

bigint &bigint::operator<<=(size_t shift) & {
  if (shift == 0 || sign() == 0) {
    return *this;
  }

  unsigned int constexpr bits_per_digit = sizeof(int) << 3;
  unsigned int const zeros_to_add_count =
      static_cast<int>(shift / bits_per_digit);
  shift &= bits_per_digit - 1;

  unsigned int bits_from_previous_digit = 0;
  unsigned int bits_for_next_digit = 0;
  auto const digits_count = size();
  auto const old_sign = sign();

  if (shift != 0) {
    const int mask = (1 << shift) - 1;
    for (int i = 0; i < digits_count; ++i) {
      bits_for_next_digit = (static_cast<bigint const *>(this)->operator[](i) >>
                             (bits_per_digit - shift)) &
                            mask;

      unsigned int result = (this->operator[](i) << static_cast<int>(shift)) |
                            bits_from_previous_digit;
      this->operator[](i) = *reinterpret_cast<int *>(&result);
      bits_from_previous_digit = bits_for_next_digit;
    }
  }

  size_t numbers_to_add_after_shift_overflows =
      (bits_from_previous_digit != 0) ? 1 : 0;

  unsigned int oldest_digit_in_new_array =
      numbers_to_add_after_shift_overflows > 0 ? bits_from_previous_digit
                                               : oldest_digit_;

  size_t
      additional_oldest_zero_to_prevent_number_to_turn_from_positive_to_negative =
          0;
  if (old_sign >= 0 && oldest_digit_ < 0) {
    additional_oldest_zero_to_prevent_number_to_turn_from_positive_to_negative =
        1;
  }

  size_t new_array_size =
      digits_count + zeros_to_add_count + numbers_to_add_after_shift_overflows +
      additional_oldest_zero_to_prevent_number_to_turn_from_positive_to_negative;
  if (new_array_size > digits_count) {
    auto *new_array = new int[new_array_size];

    std::memcpy(new_array + zeros_to_add_count, other_digits_ + 1,
                (digits_count - 1) * sizeof(int));
    new_array
        [new_array_size - 1 - numbers_to_add_after_shift_overflows -
         additional_oldest_zero_to_prevent_number_to_turn_from_positive_to_negative] =
            oldest_digit_;
    if (numbers_to_add_after_shift_overflows == 1) {
      new_array
          [new_array_size - 1 -
           additional_oldest_zero_to_prevent_number_to_turn_from_positive_to_negative] =
              *reinterpret_cast<int *>(&bits_from_previous_digit);
    }
    if (additional_oldest_zero_to_prevent_number_to_turn_from_positive_to_negative ==
        1) {
      new_array[new_array_size - 1] = 0;
    }
    std::memset(new_array, 0, zeros_to_add_count * sizeof(int));

    from_array(new_array, new_array_size);

    delete[] new_array;
  }

  remove_leading_zeros();

  return *this;
}

bigint bigint::operator<<(size_t shift) const {
  bigint copy = *this;
  return copy <<= shift;
}

bigint &bigint::operator>>=(size_t shift) & {
  int const this_sign = sign();
  if (shift == 0 || this_sign == 0) {
    return *this;
  }

  int const bits_per_digit = sizeof(int) << 3;
  int const digits_to_remove = static_cast<int>(shift / bits_per_digit);
  shift &= bits_per_digit - 1;

  if (digits_to_remove >= size()) {
    *this = 0;
    return *this;
  }

  unsigned int bits_from_previous_digit = 0;
  unsigned int bits_for_next_digit = 0;
  auto const digits_count = size();

  if (shift != 0) {
    const unsigned int mask = (1 << shift) - 1;
    for (int i = digits_count - 1; i >= 0; --i) {
      bits_for_next_digit =
          (static_cast<bigint const *>(this)->operator[](i) & mask)
          << (bits_per_digit - shift);
      unsigned int result = (static_cast<bigint const *>(this)->operator[](i) >>
                             static_cast<int>(shift)) |
                            bits_from_previous_digit;
      bits_from_previous_digit = bits_for_next_digit;
      this->operator[](i) = *reinterpret_cast<int *>(&result);
      if (this_sign == -1) {
        int const mask = INT_MIN >> (shift - 1);
        this->operator[](i) |= mask;
      }
    }
  }

  size_t new_array_size = digits_count - digits_to_remove;
  if (new_array_size == 0) {
    *this = 0;
    remove_leading_zeros();
    return *this;
  }

  if (digits_to_remove > 0) {
    auto *new_array = new int[new_array_size];
    std::memcpy(new_array, other_digits_ + 1 + digits_to_remove,
                (new_array_size - 1) * sizeof(int));
    new_array[new_array_size - 1] = oldest_digit_;

    from_array(new_array, new_array_size);
    delete[] new_array;
  }

  remove_leading_zeros();
  return *this;
}

bigint bigint::operator>>(size_t shift) const {
  bigint copy = *this;
  return copy >>= shift;
}
