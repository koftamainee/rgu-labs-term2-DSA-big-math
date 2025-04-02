#include "bigint.h"

int bigint::compare(bigint const &first, bigint const &second) {
  auto const first_size = first.size();
  auto const second_size = second.size();

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
