#include <algorithm>
#include <climits>
#include <cstring>
#include <filesystem>
#include <iostream>
#include <system_error>

#include "bigint.h"

bigint bigint::operator-() const {
  bigint negative = *this;
  return negative.negate();
}

bigint bigint::abs() const { return sign() < 0 ? -*this : *this; }

bigint &bigint::negate() & {
  if (sign() == 0) {
    return *this;
  }
  if (size() == 1 && oldest_digit_ == INT_MIN) {
    int arr[] = {INT_MIN, 0};
    return from_array(arr, 2);
  }
  if (sign() == 1) {
    bit_inverse();
    _raw_negative_increment();
    return *this;
  }

  _raw_positive_decrement();  // TODO: rewrite _raw_negative_decrement without
                              // +=
  bit_inverse();
  return *this;
}

bigint &bigint::operator++() & {
  if (sign() == -1) {
    return _raw_negative_increment();
  }

  return _raw_positive_increment();
}

bigint const bigint::operator++(int) & {
  auto const copy = *this;
  ++(*this);
  return copy;
}

bigint &bigint::operator--() & {
  if (sign() == -1) {
    return _raw_negative_decrement();
  }

  return _raw_positive_decrement();
}

bigint const bigint::operator--(int) & {
  auto const copy = *this;
  --(*this);
  return copy;
}

bigint &bigint::operator+=(bigint const &other) & {
  int this_sign = sign();
  int other_sign = other.sign();

  if (this_sign == 0) {
    return *this = other;
  }

  if (other_sign == 0) {
    return *this;
  }

  int result_sign = 0;

  if (this_sign == other_sign) {
    result_sign = this_sign;
  } else {
    const bigint abs_this = this->abs();
    const bigint abs_other = other.abs();

    if (abs_this == abs_other) {
      return *this = 0;
    }

    bool this_bigger = abs_this > abs_other;
    result_sign = this_bigger ? this_sign : other_sign;
  }

  unsigned int this_size = size();
  unsigned int other_size = other.size();
  unsigned int max_size = (this_size > other_size ? this_size : other_size) + 1;
  bool borrow_one = false;

  int *result = new int[max_size]();
  unsigned int extra_digit = 0;

  for (int i = 0; i < max_size; ++i) {
    int this_digit = (i < this_size) ? (*this)[i] : 0;
    int other_digit = (i < other_size) ? const_cast<bigint &>(other)[i] : 0;

    if (this_digit == 0 && other_digit == 0 && extra_digit == 0 &&
        !borrow_one) {
      continue;
    }

    unsigned int this_lo = loword(this_digit);
    unsigned int this_hi = hiword(this_digit);
    unsigned int other_lo = loword(other_digit);
    unsigned int other_hi = hiword(other_digit);

    unsigned int sum_lo = this_lo + other_lo + extra_digit;
    extra_digit = sum_lo >> SHIFT;
    unsigned int lo_res = sum_lo & MASK;

    unsigned int sum_hi = this_hi + other_hi + extra_digit;
    extra_digit = sum_hi >> SHIFT;
    unsigned int hi_res = sum_hi & MASK;

    unsigned int combined = (hi_res << SHIFT) | lo_res;
    result[i] = *reinterpret_cast<int *>(&combined);
    if (borrow_one) {
      if (result[i] == 0) {
        result[i] = -2;
      } else {
        --result[i];
        borrow_one = false;
      }
    }

    if ((this_digit ^ other_digit) < 0) {
      extra_digit = 0;
    }

    if (this_digit < 0 && other_digit < 0) {
      long long sum = static_cast<long long>(this_digit) + other_digit;
      if (sum < INT_MIN) {
        extra_digit = 0;
        borrow_one = true;
      } else {
        std::cout << "nothing happend!!" << std::endl;
        std::cout << "extra_digit: " << extra_digit << std::endl;
        extra_digit = 0;
        // borrow_one = true;
      }
      // std::cout << "sum: " << sum << std::endl;
      // getchar();
    }
  }
  if (borrow_one) {
    while (result[max_size - 1] == -2) {
      --max_size;
    }
    ++max_size;
    result[max_size - 1] = -1;
  }

  if (result_sign == -1 && result[max_size - 1] == 0) {
    --max_size;
  }

  move_from_array(result, max_size);
  return *this;
}

bigint operator+(bigint const &first, bigint const &second) {
  bigint temp = first;
  return temp += second;
}

bigint &bigint::operator-=(bigint const &other) & { return *this += (-other); }

bigint operator-(bigint const &first, bigint const &second) {
  return first + (-second);
}

bigint &bigint::operator*=(bigint const &other) & {
  if (this->sign() == 0 || other.sign() == 0) {
    *this = 0;
    return *this;
  }
  if (other == 1) {
    return *this;
  }
  if (*this == 1) {
    return *this = other;
  }
  if (other == -1) {
    return this->negate();
  }
  if (*this == -1) {
    return *this = -other;
  }

  if (this->sign() == -1 && other.sign() == -1) {
    return this->negate() *= -other;
  }

  if (other.sign() == -1) {
    return (*this *= -other).negate();
  }
  if (this->sign() == -1) {
    return (this->negate() *= other).negate();
  }

  return multiply(other);
}

bigint &bigint::multiply(bigint const &other) {
  // if (size() >= KARATSUBA_THRESHOLD && other.size() >=
  // KARATSUBA_THRESHOLD) {
  //   return karatsuba_multiply(other);
  // }
  return scholarbook_multiply(other);
}

bigint operator*(bigint const &first, bigint const &second) {
  bigint copy = first;
  return copy *= second;
}

bigint &bigint::operator/=(bigint const &other) & {
  return *this = std::move(division(*this, other).quotient());
}

bigint operator/(bigint const &first, bigint const &second) {
  return bigint::division(first, second).quotient();
}

bigint &bigint::operator%=(bigint const &other) & {
  return *this = std::move(division(*this, other).remainder());
}

bigint operator%(bigint const &first, bigint const &second) {
  return bigint::division(first, second).remainder();
}
