#include <stdexcept>

#include "bigint.h"
#include "cstring.h"

std::ostream &operator<<(std::ostream &out, bigint const &num) noexcept {
  for (int i = 0; i < num.size(); ++i) {
    out << const_cast<bigint &>(num)[i] << " ";
  }

  return out;
}
std::istream &operator>>(std::istream &in, bigint &num) noexcept {
  cstd::string input;
  in >> input;

  num.cleanup();
  try {
    num.from_string(input, 10);
  } catch (std::invalid_argument const &e) {
    in.setstate(std::ios::failbit);
  }

  return in;
}
