#include "cstring.h"

#include <cstring>
#include <iostream>
#include <stdexcept>

namespace cstd {

void string::resize(size_t new_size) {
  char *temp = new char[new_size];
  std::strcpy(temp, data_);
  delete[] data_;
  data_ = temp;
  temp = nullptr;
}

string::string() {
  data_ = new char[STRING_INITIAL_CAPACITY];
  capacity_ = STRING_INITIAL_CAPACITY;
  size_ = 0;
}

string::string(const string &other) {
  data_ = new char[other.capacity_];
  capacity_ = other.capacity_;
  size_ = other.size_;
  std::strcpy(data_, other.data_);
}

string::string(const char *other) {
  size_t len = std::strlen(other);
  data_ = new char[len];
  capacity_ = len;
  size_ = len;
  std::strcpy(data_, other);
}

string::~string() noexcept {
  delete[] data_;
  data_ = nullptr;
  capacity_ = 0;
  size_ = 0;
}

string &string::operator=(const string &other) {
  if (&other == this) {
    return *this;
  }
  if (capacity_ < other.size_) {
    resize(other.size_);
    capacity_ = other.size_;
  }

  std::strcpy(data_, other.data_);
  size_ = other.size_;

  return *this;
}

char &string::operator[](size_t index) const noexcept { return data_[index]; }

char &string::at(size_t index) const {
  if (index >= size_) {
    throw std::out_of_range("Index out of range of string");
  }
  return data_[index];
}

size_t string::size() const noexcept { return size_; }
size_t string::capacity() const noexcept { return capacity_; }

void string::clear() {
  if (size_ > STRING_INITIAL_CAPACITY) {
    resize(STRING_INITIAL_CAPACITY);
    capacity_ = STRING_INITIAL_CAPACITY;
  }
  size_ = 0;
}

bool string::empty() const noexcept { return size_ == 0; }

string string::operator+(string other) const { return other += *this; }

string &string::operator+=(const string &other) {
  if (capacity_ <= size_ + other.size_) {
    resize(size_ + other.size_);
  }

  std::strcat(data_, other.data_);
  size_ += other.size_;
  return *this;
}

void string::push_back(char c) {
  if (size_ + 1 == capacity_) {
    resize(capacity_ * STRING_GROWTH_FACTOR);
  }
  data_[size_++] = c;
  data_[size_] = '\0';
}

void string::insert(char c, size_t index) {
  if (index == size_) {
    push_back(c);
  }
  if (size_ == capacity_) {
    resize(capacity_ * STRING_GROWTH_FACTOR);
  }
  std::memcpy(data_ + index + 1, data_ + index, size_ - index - 1);
  ++size_;
  data_[index] = c;
}

void string::pop_back() {
  if (size_ == 0) {
    throw std::runtime_error("Can not pop_back. String is empty");
  }
  data_[--size_] = 0;
  if (capacity_ / size_ > 2) {
    resize(capacity_ / STRING_GROWTH_FACTOR);
  }
}

string string::substr(const string &needle) const { return {}; }  // TODO pls

int string::compare(const string &other) const noexcept {
  return std::strcmp(data_, other.data_);
}

[[nodiscard]] const char *string::c_str() const noexcept { return data_; }
[[nodiscard]] char *string::data() const noexcept { return data_; }

std::ostream &operator<<(std::ostream &out, const string &str) {
  out << str.data_;
  return out;
}

std::istream &operator>>(std::istream &in, string &str) {
  str.clear();

  char c;
  while (in.get(c)) {
    if (std::isspace(c) != 0) {
      break;
    }
    str.push_back(c);
  }

  return in;
}

}  // namespace cstd
