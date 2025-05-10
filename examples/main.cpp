#include <chrono>
#include <fstream>
#include <iomanip>

#include "bigint.h"

int test_bigint();
int test_bigfloat();
int bigint_performance();

bigint fibonacci_iterative(bigint const &n);

int main() {
  // benchmark_karatsuba_threshold();
  // bigint_performance();
  // test_bigint();

  int arr1[] = {-2147483648, -1000000000};

  int arr2[] = {-1, -1000000000};
  bigint res = "-8589934585557549057";

  bigint a(arr1, 2);
  bigint b(arr2, 2);

  std::cout << "-----------------------------------\n";

  std::cout << a << " + " << b << " = " << a + b << std::endl;
  std::cout << res << std::endl;

  return 0;
}
