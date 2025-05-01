#include <chrono>
#include <fstream>

#include "bigint.h"

int test_bigint();
int test_bigfloat();

bigint fibonacci_iterative(bigint const &n);

void large_performance_test() {
  using clock = std::chrono::high_resolution_clock;
  using duration = std::chrono::duration<double>;

  std::ofstream out_file("performance/performance_results.csv");
  out_file << "operation,n,time\n";

  std::cout << "Running large number performance tests...\n";

  for (int n = 10000; n <= 100000; n += 10000) {
    bigint fib_n(n);

    auto start = clock::now();
    bigint fib_result = fibonacci_iterative(fib_n);
    auto end = clock::now();
    duration elapsed = end - start;

    out_file << "fibonacci," << n << "," << elapsed.count() << "\n";
    std::cout << "Fibonacci(" << n << ") computed in " << elapsed.count()
              << "s\n";
  }

  for (int n = 1000; n <= 10000; n += 1000) {
    bigint fact_n(n);

    auto start = clock::now();
    bigint fact_result = bigint::factorial(fact_n);
    auto end = clock::now();
    duration elapsed = end - start;

    out_file << "factorial," << n << "," << elapsed.count() << "\n";
    std::cout << "Factorial(" << n << ") computed in " << elapsed.count()
              << "s\n";
  }

  out_file.close();
  std::cout << "Results saved to peroformance/performance_results.csv\n";
}

int main() {
  large_performance_test();
  // test_bigint();
  // int fact = 2000;

  // std::cout << "Computing " << fact << "!... " << std::endl;
  // auto res = fibonacci_iterative(300000);
  // auto res = bigint::factorial(fact);

  // std::cout << "Done" << std::endl;

  // std::cout << res << std::endl;

  // bigint a = 52;
  // for (int i = 0; i < 128; ++i) {
  //   a *= a;
  //   std::cout << "counted" << std::endl;
  //   // std::cout << a << std::endl;
  //   getchar();
  // }
}
