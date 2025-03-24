#include <stdexcept>

#include "bigpoly.h"

bigpoly::node *bigpoly::poly_from_str(cstd::string const &poly_str) {}

std::ostream &operator<<(std::ostream &out, bigpoly const &poly) {}

std::istream &operator>>(std::istream &in, bigpoly &poly) {
  cstd::string input;
  in >> input;
  try {
    poly.poly_ = bigpoly::poly_from_str(input);
  } catch (std::invalid_argument const &e) {
    in.setstate(std::ios::failbit);
    return in;
  }
  return in;
}
