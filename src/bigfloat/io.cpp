#include "bigfloat.h"

std::ostream &operator<<(std::ostream &out, bigfloat const &num) noexcept {
  if (num.demonimator_ < 0) {
    out << "-";
  }
  out << num.numerator_ << "/" << num.demonimator_;
  return out;
}
std::istream &operator>>(std::istream &in, bigfloat const &num) noexcept {}
