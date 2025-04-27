
#include <bitset>
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
  // test_bigint();
  // test_bigfloat();

  // print_fib();
  int arr[] = {-1, -10};
  bigint a(arr, 2);
  bigint b = -10;
  std::cout << a << " " << b << ", " << (a > b) << std::endl;
}
