#include <sstream>
#include <stdexcept>

#include "bigcomplex.h"

void bigcomplex::from_str(std::string const &complex_str) {
  std::istringstream input(complex_str.c_str());
  bigfloat real;
  bigfloat imaginary;
  char c;
  input >> real >> c;

  if (c != '+' && c != '-') {
    throw std::invalid_argument("Invalid complex number format");
  }
  input >> imaginary >> c;
  if (c != 'i') {
    throw std::invalid_argument("Invalid complex number format");
  }
  real_ = std::move(real);
  imaginary_ = std::move(imaginary);
}

std::ostream &operator<<(std::ostream &out, bigcomplex const &complex) {
  if (complex.imaginary_ < 0) {
    out << complex.real_ << " " << complex.imaginary_ << "i";
  } else {
    out << complex.real_ << " + " << complex.imaginary_ << "i";
  }
  return out;
}

std::istream &operator>>(std::istream &in, bigcomplex &complex) {
  std::string input;
  in >> input;
  try {
    complex.from_str(input);
  } catch (std::invalid_argument const &e) {
    in.setstate(std::ios::failbit);
  }
  return in;
}
