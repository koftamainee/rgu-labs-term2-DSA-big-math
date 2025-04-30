#include "bigint.h"

#include <unistd.h>

#include <cstring>
#include <optional>

bigint::bigint() noexcept : oldest_digit_(0), other_digits_(nullptr) {}

bigint::bigint(char const *value, std::size_t base)
    : oldest_digit_(0), other_digits_(nullptr) {
  from_string(value, base);
}

bigint::bigint(int const *value, std::size_t size)
    : oldest_digit_(0), other_digits_(nullptr) {
  from_array(value, size);
}

bigint::bigint(int value) noexcept
    : oldest_digit_(value), other_digits_(nullptr) {}

bigint::bigint(bigint const &other) : oldest_digit_(0), other_digits_(nullptr) {
  clone(other);
}

bigint::bigint(bigint &&other) noexcept
    : oldest_digit_(0), other_digits_(nullptr) {
  move(std::move(other));
}

bigint::~bigint() noexcept { cleanup(); }

std::optional<int> bigint::to_int() const noexcept {
  if (other_digits_ == nullptr) {
    return oldest_digit_;
  }
  return std::nullopt;
}

bigint &bigint::operator=(bigint const &other) {
  if (this != &other) {
    cleanup();
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

void bigint::cleanup() {
  delete[] other_digits_;
  other_digits_ = nullptr;
  oldest_digit_ = 0;
}
