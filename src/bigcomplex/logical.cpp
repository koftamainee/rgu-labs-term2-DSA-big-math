#include "bigcomplex.h"

bool operator==(bigcomplex const &first, bigcomplex const &other) {
  return (first.real_ == other.real_) && (first.imaginary_ == other.imaginary_);
}

bool operator!=(bigcomplex const &first, bigcomplex const &other) {
  return !(first == other);
}
