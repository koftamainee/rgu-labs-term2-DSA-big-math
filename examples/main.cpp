#include <chrono>
#include <climits>
#include <fstream>
#include <iomanip>

#include "bigint.h"

int test_bigint();
int test_bigfloat();
int bigint_performance();

bigint fibonacci_iterative(bigint const &n);

int main() {
  // bigint_performance();
  test_bigint();
  // test_bigfloat();

  return 0;
}
