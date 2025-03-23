#include "bigfloat.h"

#include <optional>
#include <utility>

bigfloat::bigfloat(bigint numerator, bigint demonimator)
    : numerator_(std::move(numerator)), demonimator_(std::move(demonimator)) {}

bigfloat::bigfloat(bigint const &other) : numerator_(other), demonimator_(1) {}

bigfloat::bigfloat(bigfloat const &other) {}

bigfloat::bigfloat(bigint &&other) noexcept {}

bigfloat::bigfloat(double num)
    : numerator_(static_cast<int>(num)), demonimator_(1) {}

std::optional<double> bigfloat::to_double() noexcept {
  auto int_numerator = numerator_.to_int();
  auto int_demonimator = demonimator_.to_int();
  if (!int_numerator || !int_demonimator) {
    return std::nullopt;
  }
  return *int_numerator / *int_demonimator;
}
