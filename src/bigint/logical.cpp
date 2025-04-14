#include "bigint.h"

int bigint::compare(bigint const &first, bigint const &second) {
  auto const first_znak = first.sign();
  auto const second_znak = second.sign();
  auto const first_size = first.size();
  auto const second_size = second.size();

  if ((first_znak == -1) && (second_znak >= 0)) {
    return -1;
  }
  if ((first_znak >= 0) && (second_znak == -1)) {
    return 1;
  }
  if ((first_znak == -1) && (second_znak == -1)) {
    auto res = compare(const_cast<bigint &>(first).negate(),
                       const_cast<bigint &>(second).negate());
    const_cast<bigint &>(first).negate();
    const_cast<bigint &>(second).negate();
    // or use
    // auto res = compare(-first, -second);
    // for thread-safe and not using const_cast
    return res > 0 ? -res : res;
  }

  if (first_size > second_size) {
    return 1;
  }
  if (second_size > first_size) {
    return -1;
  }
  for (int i = 0; i < first_size; ++i) {
    if (first[i] > second[i]) {
      return 1;
    }
    if (second[i] > first[i]) {
      return -1;
    }
  }
  return 0;
}

bool operator==(bigint const &first, bigint const &second) {
  return bigint::compare(first, second) == 0;
}
bool operator!=(bigint const &first, bigint const &second) {
  return bigint::compare(first, second) != 0;
}

bool operator<(bigint const &first, bigint const &second) {
  return bigint::compare(first, second) < 0;
}
bool operator<=(bigint const &first, bigint const &second) {
  return bigint::compare(first, second) <= 0;
}

bool operator>(bigint const &first, bigint const &second) {
  return bigint::compare(first, second) > 0;
}
bool operator>=(bigint const &first, bigint const &second) {
  return bigint::compare(first, second) >= 0;
}
