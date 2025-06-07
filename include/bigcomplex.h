#pragma once

#include <ostream>

#include "bigfloat.h"

class bigcomplex final {
 private:
  bigfloat real_;
  bigfloat imaginary_;

  void from_str(std::string const &complex_str);

 public:
  bigcomplex() = default;
  ~bigcomplex() = default;
  bigcomplex(bigcomplex const &other) = default;
  bigcomplex(bigcomplex &&other) = default;
  bigcomplex &operator=(bigcomplex const &other) = default;
  bigcomplex &operator=(bigcomplex &&other) = default;

  bigcomplex(bigfloat real_, bigfloat imaginary_ = 0);
  bigcomplex(std::string const &complex_str);

  bigcomplex operator-() const noexcept;
  bigcomplex &negate() noexcept;

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

  bigfloat arg(bigfloat const &EPS = bigfloat::DEFAULT_EPS) const;
  bigfloat abs(bigfloat const &EPS = bigfloat::DEFAULT_EPS) const;

  friend std::ostream &operator<<(std::ostream &out, bigcomplex const &complex);
  friend std::istream &operator>>(std::istream &in, bigcomplex &complex);
};
