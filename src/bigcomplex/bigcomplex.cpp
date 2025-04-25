#include "bigcomplex.h"

bigcomplex::bigcomplex(bigfloat real_, bigfloat imaginary_) {}

bigcomplex::bigcomplex(cstd::string const &complex_str) {
  from_str(complex_str);
}
