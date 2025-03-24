#include <cstring>
#include <exception>

#include "bigfloat.h"
#include "cstring.h"

std::ostream &operator<<(std::ostream &out, bigfloat const &num) noexcept {
  if (num.demonimator_ < 0) {
    out << "-";
  }
  out << num.numerator_ << "/" << num.demonimator_;
  return out;
}
std::istream &operator>>(std::istream &in, bigfloat &num) {
  cstd::string input;
  in >> input;

  char *slash_pos = std::strchr(input.data(), '/');
  if (slash_pos == nullptr) {
    in.setstate(std::ios::failbit);
    return in;
  }
  *slash_pos = '\0';
  char *numerator_str = input.data();
  char *demonimator_str = slash_pos + 1;

  char sign = '+';
  if (numerator_str[0] == '+' || numerator_str[0] == '-') {
    sign = numerator_str[0];
    ++numerator_str;
  }
  try {
    bigint numerator(numerator_str, 10);
    bigint demonimator(demonimator_str, 10);
    if (sign == '-') {
      demonimator.negate();
    }

    num.demonimator_ = std::move(demonimator);
    num.numerator_ = std::move(numerator);

  } catch (std::exception const &e) {
    in.setstate(std::ios::failbit);
    return in;
  }
  return in;
}
