#include "bigint.h"

int test_bigint();
int test_bigfloat();
int bigint_performance();

bigint fibonacci_iterative(bigint const &n);

int main() {
  bigint_performance();
  // test_bigint();
  // int arr[] = {1, 2, 3, 4};
  // bigint a(arr, 4);
  // bigint b = 15;
  // std::cout << a << " * " << b << std::endl;
  // std::cout << a * b << std::endl;
}
