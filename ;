#include <cstdio>
#include <future>
#include <numeric>

#include "bigfloat.h"

bigfloat bigfloat::PI(const bigfloat &EPS) {
  if (pi_cache_.find(EPS) != pi_cache_.cend()) {
    return pi_cache_[EPS];
  }
  static const bigfloat one_fifth(1, 5);
  static const bigfloat one_239(1, 239);

  auto future_arctg_1_5 = std::async(
      std::launch::async, [&]() { return arctg(one_fifth, EPS / 16); });
  auto future_arctg_1_239 =
      std::async(std::launch::async, [&]() { return arctg(one_239, EPS / 4); });

  const bigfloat arctg_1_5 = future_arctg_1_5.get();
  const bigfloat arctg_1_239 = future_arctg_1_239.get();

  bigfloat pi = 16 * arctg_1_5 - 4 * arctg_1_239;
  pi_cache_[EPS] = pi;
  return pi;
}

bigfloat bigfloat::reduce_argument(const bigfloat &number,
                                   const bigfloat &EPS) {
  constexpr size_t reducing_threshold = 7;
  bigfloat reduced_x = number;

  if (reduced_x > reducing_threshold) {
    bigfloat const two_pi = bigfloat::PI(EPS * 2) * 2;
    bigfloat k = (number / two_pi).truncate();
    reduced_x = number - (k * two_pi);

    if (reduced_x > two_pi) {
      reduced_x -= two_pi;
    } else if (reduced_x < -two_pi) {
      reduced_x += two_pi;
    }
  }

  return reduced_x;
}

bigfloat sin(bigfloat const &number, bigfloat const &EPS) {
  bigfloat reduced_x = bigfloat::reduce_argument(number, EPS);
  bigfloat res = 0;
  bigfloat term = reduced_x;
  bigfloat x_squared = reduced_x * reduced_x;
  bigint n = 1;

  while (term.abs() > EPS) {
    res += term;
    term *= -x_squared;
    ++n;
    term /= (2 * n - 1) * (2 * n - 2);
  }

  return res;
}

bigfloat cos(bigfloat const &number, bigfloat const &EPS) {
  bigfloat reduced_x = bigfloat::reduce_argument(number, EPS);
  bigfloat res = 0;
  bigfloat term = 1;
  bigfloat number_squared = reduced_x * reduced_x;
  bigint n = 0;

  while (term.abs() > EPS) {
    res += term;
    term *= -number_squared;
    ++n;
    term /= (2 * n - 1) * (2 * n);
  }

  return res;
}

bigfloat tg(const bigfloat &number, const bigfloat &EPS) {
  bigfloat pi = bigfloat::PI(EPS);
  bigfloat two(2);
  bigfloat half_pi = pi / two;
  bigfloat x = number;
  bool negate = false;

  // Приведение аргумента к [-π, π]
  if (x.abs() > pi) {
    x = x - (x / pi).truncate() * pi;
  }

  // Симметрии тангенса
  if (x > half_pi) {
    x = pi - x;
    negate = !negate;
    x.simplify();
  } else if (x <= -half_pi) {
    x = pi + x;
    negate = !negate;
    x.simplify();
  }
  if (x < bigfloat(0)) {
    x = -x;
    negate = !negate;
    x.simplify();
  }

  // Проверка на вертикальную асимптоту
  if (x.abs() > half_pi - EPS) {
    throw std::invalid_argument("tg: аргумент слишком близок к π/2");
  }

  // Вычисление через ряд Маклорена
  bigfloat result(0);
  bigfloat term;
  bigfloat x_squared = x * x;
  bigfloat x_power = x;

  bigfloat pow_neg4_n = bigfloat(-4);
  bigfloat pow_4_n = bigfloat(4);

  bigfloat factorial = 1;
  size_t n = 1;

  for (; n <= 1000; ++n) {
    const bigfloat &B = bigfloat::bernoulli_number(2 * n);
    bigfloat coef = B * pow_neg4_n * (bigfloat(1) - pow_4_n);

    factorial *= (2 * static_cast<int>(n) - 1) * (2 * static_cast<int>(n));

    term = coef * x_power / factorial;

    if (term.abs() < EPS) {
      break;
    }

    result += term;

    x_power *= x_squared;
    pow_neg4_n *= bigfloat(-4);
    pow_4_n *= bigfloat(4);
  }

  result.simplify();
  return negate ? -result : result;
}

bigfloat ctg(bigfloat const &number, bigfloat const &EPS) {
  return tg(number, EPS).reciprocal();
}

bigfloat sec(bigfloat const &number, bigfloat const &EPS) {
  return sin(number, EPS).reciprocal();
}

bigfloat cosec(bigfloat const &number, bigfloat const &EPS) {
  return cos(number, EPS).reciprocal();
}

bigfloat arcsin(const bigfloat &number, const bigfloat &EPS) {
  if (number.abs() > 1) {
    throw std::domain_error("arcsin is undefined for |x| > 1");
  }

  if (number.abs() > bigfloat(8, 10)) {
    const bigfloat half_pi = bigfloat::PI(EPS) / 2;
    bigfloat sign = (number > 0) ? 1 : -1;
    return sign * (half_pi - sqrt(arcsin((1 - number * number), EPS), EPS));
  }

  bigfloat term = number;
  bigfloat result = term;
  bigfloat number_squared = number * number;
  bigint n = 1;

  do {
    term *=
        number_squared * (2 * n - 1) * (2 * n - 1) / ((2 * n) * (2 * n + 1));
    result += term;
    n++;
  } while (term.abs() >= EPS);

  return result;
}

bigfloat arccos(bigfloat const &number, bigfloat const &EPS) {
  if (number.abs() > 1) {
    throw std::domain_error("arccos is undefined for |x| > 1");
  }

  return bigfloat::PI() / 2 - arcsin(number, EPS);
}

bigfloat arcctg(bigfloat const &number, bigfloat const &EPS) {
  if (number.abs() <= 1) {
    return arctg(number.reciprocal(), EPS);
  }

  bigfloat reduced_x = bigfloat::reduce_argument(number, EPS);

  bigfloat term = reduced_x.reciprocal();
  bigfloat result = term;
  bigfloat x_squared_inv = term * term;
  bigint n = 1;
  int sign = -1;

  do {
    term *= x_squared_inv;
    result += sign * term / (2 * n + 1);
    sign = -sign;
    n++;
  } while (term.abs() >= EPS);

  return result;
}

bigfloat arctg(bigfloat const &number, bigfloat const &EPS) {
  bigfloat reduced_x = bigfloat::reduce_argument(number, EPS);
  if (reduced_x.abs() > 1) {
    const bigfloat half_pi = bigfloat::PI(EPS) / 2;
    return (reduced_x > 0) ? half_pi - arctg(reduced_x.reciprocal(), EPS)
                           : -half_pi - arctg(reduced_x.reciprocal(), EPS);
  }
  if (reduced_x == 1) {
    return bigfloat::PI(EPS) / 4;
  }

  bigfloat term = reduced_x;
  bigfloat result = term;
  bigfloat number_squared = reduced_x * reduced_x;
  bigint n = 1;
  int sign = -1;

  do {
    term *= number_squared;
    result += sign * term / (2 * n + 1);
    sign = -sign;
    n++;
  } while (term.abs() >= EPS);

  return result;
}

bigfloat arcsec(bigfloat const &number, bigfloat const &EPS) {
  return arccos(number.reciprocal(), EPS);
}

bigfloat arccosec(bigfloat const &number, bigfloat const &EPS) {
  return arcsin(number.reciprocal(), EPS);
}

const bigfloat &bigfloat::bernoulli_number(size_t n) {
  if (n >= bernoulli_cache_.size()) {
    compute_bernoulli_up_to(n);
  }
  return bernoulli_cache_[n];
}

void bigfloat::compute_bernoulli_up_to(size_t n) {
  while (bernoulli_cache_.size() <= n) {
    size_t m = bernoulli_cache_.size();

    if (m % 2 == 1 && m > 1) {
      bernoulli_cache_.emplace_back(0);
      continue;
    }

    bigfloat sum(0);
    for (size_t k = 0; k < m; ++k) {
      bigfloat coef = binomial(m + 1, k);
      sum += coef * bernoulli_cache_[k];
    }

    bigfloat Bm = -sum / bigfloat(static_cast<int>(m) + 1);
    bernoulli_cache_.push_back(Bm);
  }
}

bigfloat bigfloat::binomial(size_t n, size_t k) {
  if (k == 0 || k == n) {
    return 1;
  }
  if (k > n) {
    return 0;
  }

  bigfloat res = 1;
  for (size_t i = 1; i <= k; ++i) {
    res *= bigfloat(static_cast<int>(n - k + i));
    res /= bigfloat(static_cast<int>(i));
  }
  return res;
}
