#pragma oncebigint

#include <cstddef>
#include <exception>
#include <iostream>
#include <optional>

#include "cstring.h"

class bigint;

class bigint final {
 private:
  static constexpr unsigned int SHIFT = (sizeof(int) << 2);
  static constexpr unsigned int MASK = (1 << SHIFT) - 1;

  int oldest_digit_;
  int *other_digits_;

  bigint &_raw_positive_increment();
  bigint &_raw_positive_decrement();

  bigint &_raw_negative_increment();
  bigint &_raw_negative_decrement();

  void cleanup();
  void clone(bigint const &other);
  void move(bigint &&other);

  int get_oldest_positive_bit_index() const noexcept;

  unsigned int operator[](std::size_t index) const noexcept;
  int &operator[](std::size_t index);

  int sign() const noexcept;
  int size() const noexcept;
  void remove_leading_zeros();

  static int compare(bigint const &first, bigint const &second, size_t depth);

  static unsigned int max(unsigned int first, unsigned int second) noexcept;
  static unsigned int loword(unsigned int value);
  static unsigned int hiword(unsigned int value);

  static void accumulate_multiplication(
      bigint &result, unsigned int words_multiplication_result_digits[3],
      unsigned int a, unsigned int b, size_t position_shift);

  static void remove_insignificant_numbers(int const *digits,
                                           std::size_t &size);

 public:
  class mathematical_uncertainty_exception : public std::exception {};
  class zero_division_exception : public std::exception {};

  class division_result final {
   private:
    bigint *quotient_;
    bigint *remainder_;

    void cleanup();
    void clone(division_result const &other);
    void move(division_result &&other) noexcept;

   public:
    division_result(bigint const &quotient, bigint const &remainder);
    ~division_result() noexcept;
    division_result(division_result const &other);
    division_result &operator=(division_result const &other);
    division_result(division_result &&other) noexcept;
    division_result &operator=(division_result &&other) noexcept;

    bigint quotient() const;
    bigint remainder() const;
  };

  static division_result division(bigint const &dividend,
                                  bigint const &divisor);

  bigint() noexcept;
  bigint(char const *value, std::size_t base = 10);
  bigint(int const *value, std::size_t size);
  bigint(int value) noexcept;
  bigint(bigint const &other);
  bigint(bigint &&other) noexcept;
  ~bigint() noexcept;

  bigint &from_array(int const *digits, std::size_t size);

  bigint &from_string(cstd::string const &str, std::size_t base);
  cstd::string to_string() const;

  std::optional<int> to_int() const noexcept;

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

  bigint operator~() const;
  bigint &bit_inverse() &;

  bigint &operator&=(bigint const &other) &;
  friend bigint operator&(bigint const &first, bigint const &second);

  bigint &operator|=(bigint const &other) &;
  friend bigint operator|(bigint const &first, bigint const &second);

  bigint &operator^=(bigint const &other) &;
  friend bigint operator^(bigint const &first, bigint const &second);

  bigint &operator<<=(size_t shift) &;
  bigint operator<<(size_t shift) const;

  bigint &operator>>=(size_t shift) &;
  bigint operator>>(size_t shift) const;

  friend std::ostream &operator<<(std::ostream &out,
                                  bigint const &num) noexcept;
  friend std::istream &operator>>(std::istream &in, bigint &num) noexcept;
};
