#include "bigcomplex.h"

bigcomplex::bigcomplex(bigfloat real_, bigfloat imaginary_)
    : real_(std::move(real_)), imaginary_(std::move(imaginary_)) {}

bigcomplex::bigcomplex(std::string const &complex_str) {
  from_str(complex_str);
}
