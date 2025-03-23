#include "bigint.h"

bigint &bigint::operator&=(bigint const &other) & {}
bigint operator&(bigint const &first, bigint const &second) {}

bigint &bigint::operator|=(bigint const &other) & {}
bigint operator|(bigint const &first, bigint const &second) {}

bigint &bigint::operator^=(bigint const &other) & {}
bigint operator^(bigint const &first, bigint const &second) {}

bigint &bigint::operator<<=(bigint const &other) & {}
bigint operator<<(bigint const &first, bigint const &second) {}

bigint &bigint::operator>>=(bigint const &other) & {}
bigint operator>>(bigint const &first, bigint const &second) {}
