#pragma once

#include <cstddef>
#include <iostream>
#include <optional>

class bigint final {
 private:
  static constexpr unsigned int SHIFT = (sizeof(int) << 2);
  static constexpr unsigned int MASK = (1 << SHIFT) - 1;

  int oldest_digit_;
  int *other_digits_;

  void clone(bigint const &other);
  void move(bigint &&other);

  unsigned int operator[](std::size_t index) const noexcept;
  int sign() const noexcept;
  int size() const noexcept;

  static unsigned int max(unsigned int first, unsigned int second) noexcept;
  static unsigned int loword(unsigned int value);
  static unsigned int hiword(unsigned int value);

 public:
  bigint() noexcept;
  bigint(char const *value, std::size_t base);
  bigint(int const *value, std::size_t size);
  bigint(int value) noexcept;
  bigint(bigint const &other);
  bigint(bigint &&other) noexcept;
  ~bigint() noexcept;

  std::optional<int> to_int() noexcept;

  bigint &operator=(bigint const &other);
  bigint &operator=(bigint &&other) noexcept;

  bigint operator-() const;
  bigint &negate() &;

  bigint &operator++() &;
  bigint const operator++(int) &;

  bigint &operator--() &;
  bigint const operator--(int) &;

  bigint &operator+=(bigint const &other) &;
  friend bigint operator+(bigint const &first, bigint const &second);

  bigint &operator-=(bigint const &other) &;
  friend bigint operator-(bigint const &first, bigint const &second);

  bigint &operator*=(bigint const &other) &;
  friend bigint operator*(bigint const &first, bigint const &second);

  bigint &operator/=(bigint const &other) &;
  friend bigint operator/(bigint const &first, bigint const &second);

  bigint &operator%=(bigint const &other) &;
  friend bigint operator%(bigint const &first, bigint const &second);

  bigint abs() const;

  friend bool operator==(bigint const &first, bigint const &second);
  friend bool operator!=(bigint const &first, bigint const &second);

  friend bool operator<(bigint const &first, bigint const &second);
  friend bool operator<=(bigint const &first, bigint const &second);

  friend bool operator>(bigint const &first, bigint const &second);
  friend bool operator>=(bigint const &first, bigint const &second);

  bigint operator~();

  bigint &operator&=(bigint const &other) &;
  friend bigint operator&(bigint const &first, bigint const &second);

  bigint &operator|=(bigint const &other) &;
  friend bigint operator|(bigint const &first, bigint const &second);

  bigint &operator^=(bigint const &other) &;
  friend bigint operator^(bigint const &first, bigint const &second);

  bigint &operator<<=(bigint const &other) &;
  friend bigint operator<<(bigint const &first, bigint const &second);

  bigint &operator>>=(bigint const &other) &;
  friend bigint operator>>(bigint const &first, bigint const &second);

  friend std::ostream &operator<<(std::ostream &out,
                                  bigint const &num) noexcept;
  friend std::istream &operator>>(std::istream &in, bigint &num) noexcept;
};
