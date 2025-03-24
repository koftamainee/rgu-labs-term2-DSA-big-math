#include <stdexcept>

#include "bigcomplex.h"

void bigcomplex::from_str(cstd::string const &complex_str) {}  // TODO

std::ostream &operator<<(std::ostream &out, bigcomplex const &complex) {
  if (complex.imaginary_ < 0) {
    out << complex.real_ << " " << complex.imaginary_ << "i";
  } else {
    out << complex.real_ << " + " << complex.imaginary_ << "i";
  }
  return out;
}

std::istream &operator>>(std::istream &in, bigcomplex &complex) {
  cstd::string input;
  in >> input;
  try {
    complex.from_str(input);
  } catch (std::invalid_argument const &e) {
    in.setstate(std::ios::failbit);
  }
  return in;
}
