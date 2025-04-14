#include <strings.h>

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
      index == digits_count - 1 ? &oldest_digit_ : other_digits_ + index + 1);
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

bigint &bigint::from_string(cstd::string const &str, std::size_t base) {}

cstd::string bigint::to_string() {}

bigint &bigint::from_array(int const *digits, std::size_t size) {
  if (digits == nullptr) {
    throw std::invalid_argument(
        "Pointer to digits array can't be EQ to nullptr");
  }

  if (size == 0) {
    throw std::invalid_argument("Digits count can't be EQ to 0");
  }

  cleanup();

  if (size == 1) {
    oldest_digit_ = digits[0];

    return *this;
  }

  while (size != 1 && ((digits[size - 1] == 0 && digits[size - 2] >= 0) ||
                       (digits[size - 1] == -1 && digits[size - 2] < 0))) {
    --size;
  }

  *(other_digits_ = new int[size]) = static_cast<int>(size);
  memcpy(other_digits_ + 1, digits, (size - 1) * sizeof(int));
  oldest_digit_ = digits[size - 1];

  return *this;
}
