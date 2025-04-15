#include "bigint.h"

int bigint::compare(bigint const &first, bigint const &second, size_t depth) {
  if (depth > 2) {
    std::cout << first << second << std::endl;
    throw 52;
  }
  auto const first_znak = first.sign();
  auto const second_znak = second.sign();
  auto const first_size = first.size();
  auto const second_size = second.size();
  int positives = 1;

  if ((first_znak == -1) && (second_znak >= 0)) {
    return -1;
  }
  if ((first_znak >= 0) && (second_znak == -1)) {
    return 1;
  }
  if (first_znak == -1 && second_znak == -1) {
    positives = -1;
  }
  // if ((first_znak == -1) && (second_znak == -1)) {
  //   auto res = compare(const_cast<bigint &>(first).negate(),
  //                      const_cast<bigint &>(second).negate(), depth + 1);
  //   const_cast<bigint &>(first).negate();
  //   const_cast<bigint &>(second).negate();
  //   // or use
  //   // auto res = compare(-first, -second);
  //   // for thread-safe and not using const_cast
  //   return res > 0 ? -res : res;
  // }

  if (first_size > second_size) {
    return 1 * positives;
  }
  if (second_size > first_size) {
    return -1 * positives;
  }
  for (int i = 0; i < first_size; ++i) {
    if (first[i] > second[i]) {
      return 1 * positives;
    }
    if (second[i] > first[i]) {
      return -1 * positives;
    }
  }
  return 0;
}

bool operator==(bigint const &first, bigint const &second) {
  return bigint::compare(first, second, 1) == 0;
}
bool operator!=(bigint const &first, bigint const &second) {
  return bigint::compare(first, second, 1) != 0;
}

bool operator<(bigint const &first, bigint const &second) {
  return bigint::compare(first, second, 1) < 0;
}
bool operator<=(bigint const &first, bigint const &second) {
  return bigint::compare(first, second, 1) <= 0;
}

bool operator>(bigint const &first, bigint const &second) {
  return bigint::compare(first, second, 1) > 0;
}
bool operator>=(bigint const &first, bigint const &second) {
  return bigint::compare(first, second, 1) >= 0;
}
