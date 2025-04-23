#include <strings.h>

#include <cctype>
#include <cstdio>
#include <cstring>
#include <stdexcept>

#include "bigint.h"

unsigned int bigint::max(unsigned int first, unsigned int second) noexcept {
  return first > second ? first : second;
}

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
  oldest_digit_ = other.oldest_digit_;
  if (other.other_digits_ == nullptr) {
    return;
  }
  other_digits_ = new int[other.size()];
  std::memcpy(other_digits_, other.other_digits_, other.size() * sizeof(int));
}

void bigint::move(bigint &&other) {
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

bigint &bigint::from_string(cstd::string const &str, std::size_t base) {
  if (base > 36) {
    throw std::invalid_argument("invalid base for conversion : ");
  }
  if (str.size() == 1 && str[0] == '-') {
    throw std::invalid_argument("Invalid string number representation");
  }

  *this = 0;
  bool negative = false;
  for (int i = 0; i < str.size(); ++i) {
    if (str[i] == '-') {
      negative = true;
      continue;
    }
    auto const c = str[i];
    *this *= 10;
    if (std::isdigit(c) != 0) {
      *this += c - '0';
    } else if (std::isalpha(c) != 0) {
      *this += std::toupper(c) - 'A' + 10;
    } else {
      *this = 0;
      throw std::invalid_argument(
          "invalid character in string number representation found");
    }
  }
  if (negative) {
    negate();
  }

  return *this;
}

cstd::string bigint::to_string() const {
  if (*this == bigint(0)) {
    return {"0"};
  }

  bigint num = this->abs();
  cstd::string result;

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

  *(other_digits_ = new int[size]) = static_cast<int>(size);
  memcpy(other_digits_ + 1, digits, (size - 1) * sizeof(int));
  oldest_digit_ = digits[size - 1];

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
