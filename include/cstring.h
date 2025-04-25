#pragma once

#include <cstddef>
#include <iostream>

namespace cstd {
class string {
 private:
  const size_t STRING_INITIAL_CAPACITY = 16;
  const size_t STRING_GROWTH_FACTOR = 2;

  char *data_;
  size_t size_;
  size_t capacity_;

  void resize(size_t new_capacity);

 public:
  string();
  string(const string &other);
  string(const char *other);
  ~string() noexcept;
  string &operator=(const string &other);

  char &operator[](size_t index) const noexcept;
  [[nodiscard]] char &at(size_t index) const;

  [[nodiscard]] size_t size() const noexcept;
  [[nodiscard]] size_t capacity() const noexcept;

  void clear();
  [[nodiscard]] bool empty() const noexcept;

  string operator+(const string &other) const;
  string &operator+=(const string &other);

  void push_back(char c);
  void insert(char c, size_t index);

  void pop_back();

  [[nodiscard]] string substr(size_t pos, size_t len) const;
  [[nodiscard]] int compare(const string &other) const noexcept;

  [[nodiscard]] const char *c_str() const noexcept;
  [[nodiscard]] char *data() const noexcept;

  friend std::ostream &operator<<(std::ostream &out, const string &str);
  friend std::istream &operator>>(std::istream &in, string &str);
};
}  // namespace cstd
