#include <strings.h>

#include <cstdio>
#include <cstring>
#include <stdexcept>

#include "bigint.h"

unsigned int bigint::loword(unsigned int value) { return value & MASK; }

unsigned int bigint::hiword(unsigned int value) { return value >> SHIFT; }

unsigned int bigint::operator[](std::size_t index) const noexcept {
  auto const digits_count = size();
  if (index >= digits_count) {
    return 0;
  }
  return *reinterpret_cast<unsigned int const *>(
      (index == (digits_count - 1)) ? &oldest_digit_
                                    : other_digits_ + index + 1);
}

void bigint::clone(bigint const &other) {
  cleanup();
  oldest_digit_ = other.oldest_digit_;
  if (other.other_digits_ == nullptr) {
    return;
  }
  other_digits_ = new int[other.size()];
  std::memcpy(other_digits_, other.other_digits_, other.size() * sizeof(int));
}

void bigint::move(bigint &&other) {
  cleanup();
  oldest_digit_ = other.oldest_digit_;
  other.oldest_digit_ = 0;

  other_digits_ = other.other_digits_;
  other.other_digits_ = nullptr;
}

int bigint::sign() const noexcept {
  if (oldest_digit_ == 0 && other_digits_ == nullptr) {
    return 0;
  }
  return (oldest_digit_ >= 0) ? 1 : -1;
}

int bigint::size() const noexcept {
  return other_digits_ == nullptr ? 1 : other_digits_[0];
}

int &bigint::operator[](std::size_t index) {
  auto const digits_count = size();
  if (index >= digits_count) {
    throw std::out_of_range("out of range of digits array");
  }
  return index == digits_count - 1 ? oldest_digit_
                                   : *(other_digits_ + 1 + index);
}

bigint &bigint::from_string(std::string const &str, std::size_t base) {
  if (str.empty()) {
    throw std::invalid_argument("string is empty");
  }
  if (base < 2 || base > 36) {
    throw std::invalid_argument("invalid base: must be between 2 and 36");
  }

  *this = 0;
  bool negative = false;
  size_t start_pos = 0;

  if (str[0] == '-') {
    negative = true;
    start_pos = 1;
  } else if (str[0] == '+') {
    start_pos = 1;
  }

  if (start_pos == str.size()) {
    throw std::invalid_argument("string contains only a sign character");
  }

  for (size_t i = start_pos; i < str.size(); ++i) {
    const char c = str[i];
    int value = -1;

    if (c >= '0' && c <= '9') {
      value = c - '0';
    } else if (c >= 'A' && c <= 'Z') {
      value = 10 + (c - 'A');
    } else if (c >= 'a' && c <= 'z') {
      value = 10 + (c - 'a');
    }

    if (value < 0 || static_cast<size_t>(value) >= base) {
      throw std::invalid_argument("invalid character '" + std::string(1, c) +
                                  "' for base " + std::to_string(base));
    }

    *this *= static_cast<int>(base);
    *this += value;
  }

  if (negative) {
    negate();
  }

  return *this;
}

std::string bigint::to_string() const {
  if (*this == bigint(0)) {
    return {"0"};
  }

  bigint num = this->abs();
  std::string result;

  while (num != bigint(0)) {
    division_result dr = division(num, 10);
    int digit = '0' + dr.remainder().to_int().value();
    result.push_back(static_cast<char>(digit));
    num = dr.quotient();
  }

  if (sign() < 0) {
    result.push_back('-');
  }

  for (size_t i = 0; i < result.size() / 2; ++i) {
    char temp = result[i];
    result[i] = result[result.size() - 1 - i];
    result[result.size() - 1 - i] = temp;
  }

  return result;
}

void bigint::remove_insignificant_numbers_from_digits_array(int const *digits,
                                                            std::size_t &size) {
  if (digits == nullptr) {
    throw std::invalid_argument(
        "pointer to digits array can't be EQ to nullptr");
  }

  if (size == 0) {
    throw std::invalid_argument("Digits count can't be EQ to 0");
  }

  while (size != 1 && ((digits[size - 1] == 0 && digits[size - 2] >= 0) ||
                       (digits[size - 1] == -1 && digits[size - 2] < 0))) {
    --size;
  }
}

bigint &bigint::from_array(int const *digits, std::size_t size) {
  remove_insignificant_numbers_from_digits_array(digits, size);
  cleanup();

  if (size == 1) {
    oldest_digit_ = digits[0];

    return *this;
  }

  other_digits_ = new int[size];
  other_digits_[0] = static_cast<int>(size);
  memcpy(other_digits_ + 1, digits, (size - 1) * sizeof(int));
  oldest_digit_ = digits[size - 1];

  return *this;
}

bigint &bigint::move_from_array(int *digits, std::size_t size) {
  remove_insignificant_numbers_from_digits_array(digits, size);
  cleanup();
  if (size == 1) {
    oldest_digit_ = digits[0];
    delete[] digits;
    return *this;
  }
  oldest_digit_ = digits[size - 1];
  std::memcpy(digits + 1, digits, (size - 1) * sizeof(int));
  digits[0] = static_cast<int>(size);
  other_digits_ = digits;
  digits = nullptr;
  return *this;
}

int bigint::get_oldest_positive_bit_index() const noexcept {
  int digits_count = size();
  if (digits_count == 0) {
    return 0;
  }

  int oldest_digit = oldest_digit_;

  int oldest_digit_oldest_bit_index = 0;
  while (oldest_digit != 0) {
    oldest_digit >>= 1;
    ++oldest_digit_oldest_bit_index;
  }
  return oldest_digit_oldest_bit_index +
         ((digits_count - 1) * static_cast<int>(sizeof(int) << 3)) - 1;
}

void bigint::remove_leading_zeros() {
  size_t size = this->size();
  while (size > 1 && (((*this)[size - 1] == 0 && (*this)[size - 2] >= 0))) {
    --size;
  }
  if (size < this->size()) {
    oldest_digit_ = other_digits_[size];
    other_digits_[0] = static_cast<int>(size);
  }
}

int bigint::bit_length() const noexcept {
  return get_oldest_positive_bit_index() + 1;
}

bigint bigint::get_lower(size_t m) const {
  auto const digits_count = size();
  if (m >= digits_count) {
    return *this;
  }
  if (m == 0) {
    return 0;
  }

  auto *new_digits = new int[m + 1];
  for (int i = 0; i < m; ++i) {
    new_digits[i] = const_cast<bigint *>(this)->operator[](i);
  }
  new_digits[m] = 0;
  bigint temp;
  return temp.move_from_array(new_digits, m + 1);
}

bigint bigint::get_upper(size_t m) const {
  auto const digits_count = size();
  if (m >= digits_count) {
    return 0;
  }

  const size_t upper_size = digits_count - m;
  auto *new_digits = new int[upper_size + 1];
  for (int i = 0; i < upper_size; ++i) {
    new_digits[i] = const_cast<bigint *>(this)->operator[](i + m);
  }
  new_digits[upper_size] = 0;
  bigint temp;
  return temp.move_from_array(new_digits, upper_size + 1);
}
