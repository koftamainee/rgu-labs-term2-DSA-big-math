#include <climits>
#include <utility>

#include "bigint.h"

void print_fib() {
  bigint current = 1;
  bigint previous = 0;

  while (true) {
    std::cout << current << '\n';
    previous = std::exchange(current, current + previous);
  }
}

int test_bigint();
int test_bigfloat();

int main() {
  test_bigint();
  // bigint num_a(12345);
  // bigint num_b("98765432109876543210");
  // std::cout << num_b << " - " << num_a << " = " << num_b - num_a <<
  // std::endl;
}
