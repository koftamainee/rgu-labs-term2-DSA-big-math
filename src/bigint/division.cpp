#include "bigint.h"

bigint::division_result::division_result(bigint const &quotient,
                                         bigint const &remainder)
    : quotient_(new bigint(quotient)), remainder_(new bigint(remainder)) {}

bigint::division_result::~division_result() noexcept { cleanup(); }

bigint::division_result::division_result(division_result const &other) {
  clone(other);
}

bigint::division_result &bigint::division_result::operator=(
    division_result const &other) {
  if (this != &other) {
    cleanup();
    clone(other);
  }
  return *this;
}

bigint::division_result::division_result(division_result &&other) noexcept {
  move(std::move(other));
}

bigint::division_result &bigint::division_result::operator=(
    division_result &&other) noexcept {
  if (this != &other) {
    cleanup();
    move(std::move(other));
  }
  return *this;
}

bigint bigint::division_result::quotient() const { return *quotient_; }

bigint bigint::division_result::remainder() const { return *remainder_; }

void bigint::division_result::cleanup() {
  delete quotient_;
  delete remainder_;
  quotient_ = nullptr;
  remainder_ = nullptr;
}

void bigint::division_result::clone(division_result const &other) {
  quotient_ = new bigint(*other.quotient_);
  remainder_ = new bigint(*other.remainder_);
}

void bigint::division_result::move(division_result &&other) noexcept {
  quotient_ = other.quotient_;
  other.quotient_ = nullptr;
  remainder_ = other.remainder_;
  other.remainder_ = nullptr;
}

bigint::division_result bigint::division(bigint const &dividend,
                                         bigint const &divisor) {
  int dividend_sign = dividend.sign();
  int divisor_sign = divisor.sign();

  if (divisor_sign == 0) {
    if (dividend_sign == 0) {
      throw mathematical_uncertainty_exception();
    }
    throw zero_division_exception();
  }

  if (dividend_sign == 0) {
    return {0, 0};
  }

  if (dividend_sign == -1 || divisor_sign == -1) {
    bigint abs_dividend = dividend.abs();
    bigint abs_divisor = divisor.abs();

    division_result positive_result = division(abs_dividend, abs_divisor);

    if (dividend_sign == -1 && divisor_sign == -1) {
      return {positive_result.quotient(), positive_result.remainder()};
    }
    if (dividend_sign == -1) {
      if (positive_result.remainder() == 0) {
        return {-positive_result.quotient(), 0};
      }
      if (dividend_sign == -1) {
        if (positive_result.remainder() == 0) {
          return {-positive_result.quotient(), 0};
        }
        return {-positive_result.quotient() - 1,
                abs_divisor - positive_result.remainder()};
      }
    }
    return {-positive_result.quotient(), positive_result.remainder()};
  }

  if (dividend < divisor) {
    return {0, dividend};
  }

  bigint quotient = 0;
  bigint remainder = dividend;
  int divisor_oldest_bit_index = divisor.get_oldest_positive_bit_index();

  while (remainder >= divisor) {
    int remainder_oldest_bit_index = remainder.get_oldest_positive_bit_index();

    int shift = remainder_oldest_bit_index - divisor_oldest_bit_index;

    bigint shifted_divisor = divisor << shift;

    if (shifted_divisor > remainder) {
      shifted_divisor >>= 1;
      --shift;
    }

    shifted_divisor.negate();

    remainder += shifted_divisor;

    bigint one = 1;
    _add_with_shift(quotient, one, shift);
  }

  quotient.remove_leading_zeros();
  remainder.remove_leading_zeros();

  return {quotient, remainder};
}
