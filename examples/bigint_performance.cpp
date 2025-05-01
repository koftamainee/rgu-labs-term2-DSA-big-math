#include <chrono>
#include <fstream>

#include "bigint.h"

bigint fibonacci_iterative(bigint const &n);

void bigint_performance() {
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
