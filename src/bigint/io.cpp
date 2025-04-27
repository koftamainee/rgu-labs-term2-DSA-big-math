#include <bitset>
#include <stdexcept>

#include "bigint.h"
#include "cstring.h"

std::ostream &operator<<(std::ostream &out, bigint const &num) noexcept {
  // auto const digits_count = num.size();
  // if (digits_count > 1) {
  //   out << "[";
  // }
  // for (int i = 0; i < num.size(); ++i) {
  //   out << const_cast<bigint &>(num)[i];
  //   if (i != num.size() - 1) {
  //     out << ", ";
  //   }
  // }
  // if (digits_count > 1) {
  //   out << "]";
  // }
  //
  // return out;

  out << num.to_string();
  return out;
}
std::istream &operator>>(std::istream &in, bigint &num) {
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
