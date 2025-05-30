#include <cstring>
#include <exception>

#include "bigfloat.h"
#include "cstring.h"

std::ostream &operator<<(std::ostream &out, bigfloat const &num) noexcept {
  if (num == 0) {
    out << 0;
    return out;
  }
  if (num.denominator_ < 0) {
    out << "-";
  }
  if (num.denominator_ != 1) {
    out << num.numerator_ << "/" << num.denominator_.abs();
  } else {
    out << num.numerator_;
  }
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
  char *denominator_str = slash_pos + 1;

  char sign = '+';
  if (numerator_str[0] == '+' || numerator_str[0] == '-') {
    sign = numerator_str[0];
    ++numerator_str;
  }
  try {
    bigint numerator(numerator_str, 10);
    bigint denominator(denominator_str, 10);
    if (sign == '-') {
      denominator.negate();
    }

    num.denominator_ = std::move(denominator);
    num.numerator_ = std::move(numerator);

  } catch (std::exception const &e) {
    in.setstate(std::ios::failbit);
    return in;
  }
  return in;
}
