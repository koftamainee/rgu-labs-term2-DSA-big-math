#include <cmath>
#include <stdexcept>

#include "bigcomplex.h"
#include "bigfloat.h"

bigcomplex bigcomplex::operator-() const noexcept {
  auto temp = *this;
  return temp.negate();
}

bigcomplex &bigcomplex::negate() noexcept {
  real_.negate();
  imaginary_.negate();
  return *this;
}

bigcomplex &bigcomplex::operator+=(bigcomplex const &other) & {
  real_ += other.real_;
  imaginary_ += other.imaginary_;
  return *this;
}
bigcomplex operator+(bigcomplex const &first, bigcomplex const &second) {
  auto temp = first;
  temp += second;
  return temp;
}

bigcomplex &bigcomplex::operator-=(bigcomplex const &other) & {
  return *this += -other;
}
bigcomplex operator-(bigcomplex const &first, bigcomplex const &second) {
  auto temp = first;
  return temp -= second;
}

bigcomplex &bigcomplex::operator*=(bigcomplex const &other) & {
  real_ = (real_ * other.real_) - (imaginary_ * other.imaginary_);
  imaginary_ = (real_ * other.imaginary_) + (imaginary_ * other.real_);
  return *this;
}

bigcomplex operator*(bigcomplex const &first, bigcomplex const &second) {
  auto temp = first;
  return temp *= second;
}

bigcomplex &bigcomplex::operator/=(bigcomplex const &other) & {
  if (other.real_ == 0 && other.imaginary_ == 0) {
    throw std::invalid_argument("Division by zero");
  }
  bigfloat denominator =
      (other.real_ * other.real_) + (other.imaginary_ * other.imaginary_);

  real_ = (real_ * other.real_ + imaginary_ * other.imaginary_) / denominator;
  imaginary_ =
      (imaginary_ * other.real_ - real_ * other.imaginary_) / denominator;

  return *this;
}

bigcomplex operator/(bigcomplex const &first, bigcomplex const &second) {
  auto temp = first;
  return temp /= second;
}

bigfloat bigcomplex::arg(bigfloat const &EPS) const {
  return arctg(real_ / imaginary_, EPS);
}

bigfloat bigcomplex::abs(bigfloat const &EPS) const {
  return sqrt((real_ * real_) + (imaginary_ * imaginary_), EPS);
}
