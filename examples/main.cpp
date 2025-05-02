#include <chrono>
#include <fstream>
#include <iomanip>

#include "bigint.h"

int test_bigint();
int test_bigfloat();
int bigint_performance();

bigint fibonacci_iterative(bigint const &n);

// void benchmark_karatsuba_threshold() {
//   const int min_threshold = 4;
//   const int max_threshold = 512;
//   const int step = 4;
//
//   const int col_width = 15;
//   std::cout << std::left;
//
//   std::ofstream csv_file("performance/karatsuba_benchmark.csv");
//   if (!csv_file.is_open()) {
//     std::cerr << "Error: Could not open CSV file for writing\n";
//     return;
//   }
//
//   std::cout << "\nBenchmarking Karatsuba Multiplication Thresholds\n";
//   std::cout << "Testing thresholds from " << min_threshold << " to "
//             << max_threshold << " with step " << step << "\n";
//   std::cout << "Calculating factorials from 1000 to 10000 in steps of
//   1000\n\n";
//
//   std::cout << std::setw(col_width) << "Threshold" << std::setw(col_width)
//             << "Time (ms)" << "\n";
//   std::cout << std::string(30, '-') << "\n";
//
//   csv_file << "Threshold,Time(ms)\n";
//
//   for (int threshold = min_threshold; threshold <= max_threshold;
//        threshold += step) {
//     bigint::KARATSUBA_THRESHOLD = threshold;
//
//     auto start = std::chrono::high_resolution_clock::now();
//
//     for (int i = 1000; i <= 10000; i += 1000) {
//       auto res = bigint::factorial(i);
//     }
//
//     auto end = std::chrono::high_resolution_clock::now();
//     auto duration =
//         std::chrono::duration_cast<std::chrono::milliseconds>(end - start)
//             .count();
//
//     std::cout << std::setw(col_width) << threshold << std::setw(col_width)
//               << duration << "\n";
//
//     csv_file << threshold << "," << duration << "\n";
//   }
//
//   std::cout
//       << "\nBenchmark completed. Results saved to
//       'karatsuba_benchmark.csv'\n";
//   csv_file.close();
// }

int main() {  // benchmark_karatsuba_threshold();
  // bigint_performance();
  // test_bigint();

  // std::cout << "begin computing..." << std::endl;
  // auto res = bigint::factorial(1000);
  // std::cout << "Done" << std::endl;
  // std::cout << res << std::endl;

  bigint a =
      "987654321098765431256874444444444444444444444444444444999999999999999999"
      "99999999999999999999999999999999999999999999999999999999999999210";
  bigint b =
      "123456778912840918240981209481264444444444444444444444444444444444444999"
      "999999999999999999999999999999999999999999999999999999999999999999999999"
      "999999999999999999999999999999999999999999999999999999999999999999999999"
      "999999999999999999999999999999999999999999999999999999999999999999999999"
      "999999999999999999999999999999999999999999999999999999999999999999999999"
      "999999999999999999999999999999999999999999999999999999999999999999999999"
      "999999999999999999999999999999999999999999999999999999999999999999999999"
      "9999999999999999999999999999999999"
      "999999999999999999999999999999999999999999999999999999999999999102840912"
      "4912684725619955555555765472654762"
      "514876512674512764576812547615267841582764";
  std::cout << a << " * " << b << " = ";
  std::cout.flush();
  std::cout << a * b << std::endl;
}
