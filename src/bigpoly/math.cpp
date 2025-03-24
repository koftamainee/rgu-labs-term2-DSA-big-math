#include "bigpoly.h"

bigpoly &bigpoly::operator+=(bigpoly const &other) & {}

bigpoly bigpoly::operator+(bigpoly other) {}

bigpoly &bigpoly::operator-=(bigpoly const &other) & {}

bigpoly bigpoly::operator-(bigpoly other) {}

bigpoly &bigpoly::operator*=(bigpoly const &other) & {}

bigpoly bigpoly::operator*(bigpoly other) {}

bigpoly &bigpoly::operator/=(bigpoly const &other) & {}

bigpoly bigpoly::operator/(bigpoly other) {}

bigpoly bigpoly::diff() const {}

bigpoly bigpoly::integral() const {}
