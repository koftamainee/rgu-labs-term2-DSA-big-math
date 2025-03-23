#include <cstring>
#include <exception>

#include "bigfloat.h"

[[nodiscard]] char *bigfloat::read_string(std::istream &in) {
  std::size_t size = 0;
  std::size_t capacity = 16;
  char *buffer = new char[capacity];

  while (true) {
    auto c = in.get();
    if (size == capacity) {
      auto *temp = new char[capacity * 2];
      std::memcpy(temp, buffer, size * sizeof(char));
      delete[] buffer;
      buffer = temp;
      capacity *= 2;
    }
    if (c == '\n' || c == EOF) {
      buffer[size++] = '\0';
      break;
    }
    buffer[size++] = static_cast<char>(c);
  }

  return buffer;
}

std::ostream &operator<<(std::ostream &out, bigfloat const &num) noexcept {
  if (num.demonimator_ < 0) {
    out << "-";
  }
  out << num.numerator_ << "/" << num.demonimator_;
  return out;
}
std::istream &operator>>(std::istream &in, bigfloat &num) {
  char *input = bigfloat::read_string(in);

  char *slash_pos = std::strchr(input, '/');
  if (slash_pos == nullptr) {
    in.setstate(std::ios::failbit);
    delete[] input;
    return in;
  }
  *slash_pos = '\0';
  char *numerator_str = input;
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
  delete[] input;
  return in;
}
