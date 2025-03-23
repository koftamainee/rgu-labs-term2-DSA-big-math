#include "bigfloat.h"

bigfloat::bigfloat(bigint const &numerator, bigint const &demonimator) {}
bigfloat::bigfloat(bigint const &num) {}
bigfloat::bigfloat(double num) {}
bigfloat::bigfloat(bigfloat const &other) {}

std::optional<double> bigfloat::to_double() {}

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

bool operator==(bigfloat const &first, bigfloat const &second) {}
bool operator!=(bigfloat const &first, bigfloat const &second) {}

bool operator<(bigfloat const &first, bigfloat const &second) {}
bool operator<=(bigfloat const &first, bigfloat const &second) {}

bool operator>(bigfloat const &first, bigfloat const &second) {}
bool operator>=(bigfloat const &first, bigfloat const &second) {}

std::ostream &operator<<(std::ostream &out, bigfloat const &num) {}
std::istream &operator>>(std::istream &in, bigfloat const &num) {}

bigfloat sin(bigfloat const &number, bigfloat const &EPS) {}
bigfloat tg(bigfloat const &number, bigfloat const &EPS) {}
bigfloat ctg(bigfloat const &number, bigfloat const &EPS) {}
bigfloat sec(bigfloat const &number, bigfloat const &EPS) {}
bigfloat cosec(bigfloat const &number, bigfloat const &EPS) {}
bigfloat arcsin(bigfloat const &number, bigfloat const &EPS) {}
bigfloat arccos(bigfloat const &number, bigfloat const &EPS) {}
bigfloat arctg(bigfloat const &number, bigfloat const &EPS) {}
bigfloat arcctg(bigfloat const &number, bigfloat const &EPS) {}
bigfloat arcsec(bigfloat const &number, bigfloat const &EPS) {}
bigfloat arccosec(bigfloat const &number, bigfloat const &EPS) {}

bigfloat pow(bigfloat const &base, bigint const &exp) {}
bigfloat radical(bigfloat const &radicand, bigint const &index,
                 bigfloat const &EPS) {}
bigfloat sqrt(bigfloat const &radicand, bigfloat const &EPS) {}

bigfloat log2(bigfloat const &number, bigfloat const &EPS) {}
bigfloat log(bigfloat const &number, bigfloat const &EPS) {}
bigfloat log10(bigfloat const &number, bigfloat const &EPS) {}
