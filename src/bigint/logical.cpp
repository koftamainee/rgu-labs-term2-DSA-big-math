#include "bigint.h"

int bigint::compare(bigint const &first, bigint const &second) {
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
  if (first_size > second_size) {
    return 1 * positives;
  }
  if (second_size > first_size) {
    return -1 * positives;
  }
  for (int i = first_size - 1; i >= 0; --i) {
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
