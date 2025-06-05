#include <stdexcept>
#include <vector>

#include "bigint.h"

bigint bigint::factorial(const bigint &n) {
  if (n < 2) return 1;
  std::vector<bigint> nums;
  for (int i = 2; i <= n; ++i) {
    nums.push_back(i);
  }
  // Умножаем попарно, пока не останется одно число
  while (nums.size() > 1) {
    std::vector<bigint> new_nums;
    for (size_t i = 0; i < nums.size(); i += 2) {
      if (i + 1 < nums.size()) {
        new_nums.push_back(nums[i] * nums[i + 1]);
      } else {
        new_nums.push_back(nums[i]);
      }
    }
    nums = std::move(new_nums);
  }
  return nums[0];
}

bigint bigint::gcd(bigint a, bigint b) {
  a = a < 0 ? -a : a;
  b = b < 0 ? -b : b;

  if (a == 0) {
    return b;
  }
  if (b == 0) {
    return a;
  }

  int shift = 0;
  while (((a | b) & 1) == 0) {
    a >>= 1;
    b >>= 1;
    ++shift;
  }

  while ((a & 1) == 0) {
    a >>= 1;
  }

  do {
    while ((b & 1) == 0) {
      b >>= 1;
    }
    if (a > b) {
      auto temp = a;
      a = b;
      b = temp;
    }
    b -= a;
  } while (b != 0);

  return a << shift;
}

bigint bigint::pow(bigint const &exponent) const {}

bigint bigint::mod_pow(bigint exponent, bigint const &modulus) const {}
