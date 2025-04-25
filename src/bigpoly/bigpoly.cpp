#include "bigpoly.h"

#include "cstring.h"

void bigpoly::clone(bigpoly const &other) { poly_ = clone_node(other.poly_); }

bigpoly::node *bigpoly::clone_node(node *root) {
  if (root == nullptr) {
    return nullptr;
  }
  auto *new_node = new node(root->coef_, root->degree_);
  new_node->next_ = clone_node(root->next_);
  return new_node;
}

void bigpoly::cleanup() noexcept {
  auto *current = poly_;
  while (current != nullptr) {
    auto *next = current->next_;
    delete current;
    current = next;
  }
}

bigpoly::bigpoly() noexcept : poly_(nullptr) {}

bigpoly::bigpoly(cstd::string const &poly_str) {
  poly_ = poly_from_str(poly_str);
}

bigpoly::~bigpoly() noexcept { cleanup(); }

bigpoly::bigpoly(bigpoly const &other) { clone(other); }

bigpoly::bigpoly(bigpoly &&other) noexcept {
  poly_ = other.poly_;
  other.poly_ = nullptr;
}

bigpoly &bigpoly::operator=(bigpoly const &other) {
  if (this != &other) {
    cleanup();
    clone(other);
  }
  return *this;
}

bigpoly &bigpoly::operator=(bigpoly &&other) noexcept {
  if (this != &other) {
    poly_ = other.poly_;
    other.poly_ = nullptr;
  }
  return *this;
}
