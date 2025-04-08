#include "bigint.h"

std::ostream &operator<<(std::ostream &out, bigint const &num) noexcept {
  for (int i = 0; i < num.size(); ++i) {
    out << const_cast<bigint &>(num)[i] << " ";
  }

  return out;
}
std::istream &operator>>(std::istream &in, bigint &num) noexcept {}
