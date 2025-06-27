#pragma once

#include <map>
#include <ostream>
#include <string>
#include <vector>

#include "bigint.h"

class bigfloat final {
 private:
  bigint numerator_;
  bigint denominator_;

  static std::map<bigfloat, bigfloat> pi_cache_;
  static std::vector<bigfloat> bernoulli_cache_;

  void simplify();

  static const bigfloat &bernoulli_number(size_t n);
  static bigfloat binomial(size_t n, size_t k);

  static bigfloat reduce_argument(const bigfloat &number, const bigfloat &EPS);

 public:
  static const bigfloat DEFAULT_EPS;

  static void compute_bernoulli_up_to(size_t n);

  bigfloat();
  bigfloat(bigint const &numerator, bigint const &denominator);
  bigfloat(bigint const &other);
  bigfloat(int other);
  bigfloat(bigfloat const &other) = default;
  bigfloat(bigfloat &&other) noexcept = default;
  ~bigfloat() noexcept = default;

  bigfloat &operator=(bigfloat const &other) = default;
  bigfloat &operator=(bigfloat &&other) = default;

  bigfloat operator-() const;
  bigfloat &negate();

  bigfloat &operator+=(bigfloat const &other) &;
  bigfloat &operator-=(bigfloat const &other) &;
  bigfloat &operator*=(bigfloat const &other) &;
  bigfloat &operator/=(bigfloat const &other) &;

  bigfloat abs() const;
  bigfloat reciprocal() const;
  bigfloat truncate() const;

  friend bigfloat operator+(bigfloat const &first, bigfloat const &second);
  friend bigfloat operator-(bigfloat const &first, bigfloat const &second);
  friend bigfloat operator*(bigfloat const &first, bigfloat const &second);
  friend bigfloat operator/(bigfloat const &first, bigfloat const &second);

  friend bool operator==(bigfloat const &first, bigfloat const &second);
  friend bool operator!=(bigfloat const &first, bigfloat const &second);
  friend bool operator<(bigfloat const &first, bigfloat const &second);
  friend bool operator<=(bigfloat const &first, bigfloat const &second);
  friend bool operator>(bigfloat const &first, bigfloat const &second);
  friend bool operator>=(bigfloat const &first, bigfloat const &second);

  friend std::ostream &operator<<(std::ostream &out,
                                  bigfloat const &num) noexcept;
  friend std::istream &operator>>(std::istream &in, bigfloat &num);

  std::string to_decimal(size_t precision = 10) const;

  // Trigonometric functions
  friend bigfloat sin(bigfloat const &number, bigfloat const &EPS);
  friend bigfloat cos(bigfloat const &number, bigfloat const &EPS);
  friend bigfloat tg(bigfloat const &number, bigfloat const &EPS);
  friend bigfloat ctg(bigfloat const &number, bigfloat const &EPS);
  friend bigfloat sec(bigfloat const &number, bigfloat const &EPS);
  friend bigfloat cosec(bigfloat const &number, bigfloat const &EPS);
  friend bigfloat arcsin(bigfloat const &number, bigfloat const &EPS);
  friend bigfloat arccos(bigfloat const &number, bigfloat const &EPS);
  friend bigfloat arctg(bigfloat const &number, bigfloat const &EPS);
  friend bigfloat arcctg(bigfloat const &number, bigfloat const &EPS);
  friend bigfloat arcsec(bigfloat const &number, bigfloat const &EPS);
  friend bigfloat arccosec(bigfloat const &number, bigfloat const &EPS);

  // Exponential and root functions
  friend bigfloat pow(bigfloat const &base, bigint const &exp);
  friend bigfloat radical(bigfloat const &radicand, bigint const &index,
                          bigfloat const &EPS);
  friend bigfloat sqrt(bigfloat const &radicand, bigfloat const &EPS);

  // Logarithmic functions
  friend bigfloat log2(bigfloat const &number, bigfloat const &EPS);
  friend bigfloat log(bigfloat const &number, bigfloat const &EPS);
  friend bigfloat log10(bigfloat const &number, bigfloat const &EPS);

  static bigfloat PI(bigfloat const &EPS = DEFAULT_EPS);
};

// Free function declarations with default EPS
bigfloat sin(bigfloat const &number,
             bigfloat const &EPS = bigfloat::DEFAULT_EPS);
bigfloat cos(bigfloat const &number,
             bigfloat const &EPS = bigfloat::DEFAULT_EPS);
bigfloat tg(bigfloat const &number,
            bigfloat const &EPS = bigfloat::DEFAULT_EPS);
bigfloat ctg(bigfloat const &number,
             bigfloat const &EPS = bigfloat::DEFAULT_EPS);
bigfloat sec(bigfloat const &number,
             bigfloat const &EPS = bigfloat::DEFAULT_EPS);
bigfloat cosec(bigfloat const &number,
               bigfloat const &EPS = bigfloat::DEFAULT_EPS);
bigfloat arcsin(bigfloat const &number,
                bigfloat const &EPS = bigfloat::DEFAULT_EPS);
bigfloat arccos(bigfloat const &number,
                bigfloat const &EPS = bigfloat::DEFAULT_EPS);
bigfloat arctg(bigfloat const &number,
               bigfloat const &EPS = bigfloat::DEFAULT_EPS);
bigfloat arcctg(bigfloat const &number,
                bigfloat const &EPS = bigfloat::DEFAULT_EPS);
bigfloat arcsec(bigfloat const &number,
                bigfloat const &EPS = bigfloat::DEFAULT_EPS);
bigfloat arccosec(bigfloat const &number,
                  bigfloat const &EPS = bigfloat::DEFAULT_EPS);

bigfloat radical(bigfloat const &radicand, bigint const &index,
                 bigfloat const &EPS = bigfloat::DEFAULT_EPS);
bigfloat sqrt(bigfloat const &radicand,
              bigfloat const &EPS = bigfloat::DEFAULT_EPS);

bigfloat log2(bigfloat const &number,
              bigfloat const &EPS = bigfloat::DEFAULT_EPS);
bigfloat log(bigfloat const &number,
             bigfloat const &EPS = bigfloat::DEFAULT_EPS);
bigfloat log10(bigfloat const &number,
               bigfloat const &EPS = bigfloat::DEFAULT_EPS);

bigfloat PI(bigfloat const &EPS = bigfloat::DEFAULT_EPS);
