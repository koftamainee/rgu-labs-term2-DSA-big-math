#pragma once

#include <ostream>

#include "bigfloat.h"
#include "cstring.h"

class bigcomplex final {
 private:
  bigfloat real_;
  bigfloat imaginary_;

  void from_str(cstd::string const &complex_str);

 public:
  bigcomplex() = default;
  ~bigcomplex() = default;
  bigcomplex(bigcomplex const &other) = default;
  bigcomplex(bigcomplex &&other) = default;
  bigcomplex &operator=(bigcomplex const &other) = default;
  bigcomplex &operator=(bigcomplex &&other) = default;

  bigcomplex(bigfloat real_, bigfloat imaginary_ = 0);
  bigcomplex(cstd::string const &complex_str);

  bigcomplex &operator+=(bigcomplex const &other) &;
  friend bigcomplex operator+(bigcomplex const &first,
                              bigcomplex const &second);

  bigcomplex &operator-=(bigcomplex const &other) &;
  friend bigcomplex operator-(bigcomplex const &first,
                              bigcomplex const &second);

  bigcomplex &operator*=(bigcomplex const &other) &;
  friend bigcomplex operator*(bigcomplex const &first,
                              bigcomplex const &second);

  bigcomplex &operator/=(bigcomplex const &other) &;
  friend bigcomplex operator/(bigcomplex const &first,
                              bigcomplex const &second);

  friend bool operator==(bigcomplex const &first, bigcomplex const &other);
  friend bool operator!=(bigcomplex const &first, bigcomplex const &other);

  friend std::ostream &operator<<(std::ostream &out, bigcomplex const &complex);
  friend std::istream &operator>>(std::istream &in, bigcomplex &complex);
};
