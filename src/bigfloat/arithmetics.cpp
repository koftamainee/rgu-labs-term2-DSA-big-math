#include "bigfloat.h"

bigfloat bigfloat::operator-() const {}
bigfloat &bigfloat::negate() {}

bigfloat &bigfloat::operator=(bigfloat const &other) {}

bigfloat &bigfloat::operator+=(bigfloat const &other) & {}

bigfloat operator+(bigfloat const &first, bigfloat const &second) {}

bigfloat &bigfloat::operator-=(bigfloat const &other) & {}

bigfloat operator-(bigfloat const &first, bigfloat const &second) {}

bigfloat &bigfloat::operator*=(bigfloat const &other) & {}

bigfloat operator*(bigfloat const &first, bigfloat const &second) {}

bigfloat &bigfloat::operator/=(bigfloat const &other) & {}

bigfloat operator/(bigfloat const &first, bigfloat const &second) {}

bigfloat &bigfloat::operator%=(bigfloat const &other) & {}

bigfloat operator%(bigfloat const &first, bigfloat const &second) {}
