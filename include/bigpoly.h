#pragma once

#include <ostream>

#include "bigfloat.h"
#include "cstring.h"

class bigpoly final {
 private:
  class node final {
   public:
    bigfloat coef_;
    unsigned int degree_;
    node *next_;

    node(bigfloat const &coef, unsigned int degree) noexcept;
  };

  node *poly_;

  void clone(bigpoly const &other);
  static node *clone_node(node *root);
  void cleanup() noexcept;
  static node *poly_from_str(cstd::string const &poly_str);

 public:
  bigpoly() noexcept;
  bigpoly(cstd::string const &poly_str);
  ~bigpoly() noexcept;
  bigpoly(bigpoly const &other);
  bigpoly(bigpoly &&other) noexcept;
  bigpoly &operator=(bigpoly const &other);
  bigpoly &operator=(bigpoly &&other) noexcept;

  bigpoly &operator+=(bigpoly const &other) &;
  bigpoly operator+(bigpoly other);

  bigpoly &operator-=(bigpoly const &other) &;
  bigpoly operator-(bigpoly other);

  bigpoly &operator*=(bigpoly const &other) &;
  bigpoly operator*(bigpoly other);

  bigpoly &operator/=(bigpoly const &other) &;
  bigpoly operator/(bigpoly other);

  bool operator==(bigpoly const &other) const noexcept;
  bool operator!=(bigpoly const &other) const noexcept;

  bigpoly diff() const;
  bigpoly integral() const;

  friend std::ostream &operator<<(std::ostream &out, bigpoly const &poly);
  friend std::istream &operator>>(std::istream &in, bigpoly &poly);
};
