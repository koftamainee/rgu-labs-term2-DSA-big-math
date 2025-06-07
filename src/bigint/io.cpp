#include <climits>
#include <cmath>
#include <ostream>
#include <stack>
#include <stdexcept>

#include "bigint.h"

std::ostream& operator<<(std::ostream& out, bigint const& num) noexcept {
  if (num == bigint(0)) {
    out << '0';
    return out;
  }

  constexpr int int_bits = (sizeof(int) * CHAR_BIT) - 1;
  const int max_power = static_cast<int>(std::log10(1ULL << int_bits));
  const bigint divisor = [max_power]() {
    bigint d = 1;
    for (int i = 0; i < max_power; ++i) {
      d *= 10;
    }
    return d;
  }();

  bigint n = num.abs();
  std::stack<std::string> chunks;

  while (n != bigint(0)) {
    bigint::division_result dr = bigint::division(n, divisor);
    int chunk = dr.remainder().to_int().value();
    chunks.push(std::to_string(chunk));
    n = dr.quotient();
  }

  if (num.sign() < 0) {
    out << '-';
  }
  out << chunks.top();
  chunks.pop();

  while (!chunks.empty()) {
    const std::string& chunk = chunks.top();
    out << std::string(max_power - chunk.length(), '0') << chunk;
    chunks.pop();
  }

  return out;
}

std::istream& operator>>(std::istream& in, bigint& num) {
  std::string input;
  in >> input;

  num.cleanup();
  try {
    num.from_string(input, 10);
  } catch (std::invalid_argument const& e) {
    in.setstate(std::ios::failbit);
  }

  return in;
}
