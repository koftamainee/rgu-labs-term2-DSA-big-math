#include <cstring>
#include <optional>
#include <stdexcept>

#include "bigint.h"

bigint::bigint() noexcept : oldest_digit_(0), other_digits_(nullptr) {}

bigint::bigint(char const *value, std::size_t base) {}  // TODO

bigint::bigint(int const *value, std::size_t size) {
  if (value == nullptr) {
    throw std::invalid_argument("value is nullptr");
  }
  if (size == 0) {
    throw std::invalid_argument("size of array can not be 0");
  }

  if (size == 1) {
    other_digits_ = nullptr;
    oldest_digit_ = value[0];
    return;
  }

  other_digits_ = new int[size];
  other_digits_[0] = static_cast<int>(size);
  memcpy(other_digits_ + 1, value, (size - 1) * sizeof(int));
  oldest_digit_ = value[size - 1];

  // TODO: Ernest must remove extra non-valuable digits
}

bigint::bigint(int value) noexcept
    : oldest_digit_(value), other_digits_(nullptr) {}

bigint::bigint(bigint const &other) { clone(other); }

bigint::bigint(bigint &&other) noexcept { move(std::move(other)); }

bigint::~bigint() noexcept { delete[] other_digits_; }

std::optional<int> bigint::to_int() noexcept {
  if (other_digits_ == nullptr) {
    return oldest_digit_;
  }
  return std::nullopt;
}

bigint &bigint::operator=(bigint const &other) {
  if (this != &other) {
    delete[] other_digits_;
    clone(other);
  }

  return *this;
}

bigint &bigint::operator=(bigint &&other) noexcept {
  if (this != &other) {
    move(std::move(other));
  }
  return *this;
}
