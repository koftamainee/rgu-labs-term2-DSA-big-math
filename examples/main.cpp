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

int main() {
  // benchmark_karatsuba_threshold();
  // bigint_performance();
  // test_bigint();

  // bigint num_a = 12345;
  // bigint num_b = "98765432109876543210";
  // num_a.negate();
  //
  // bigint diff_val = num_b + num_a;
  // bigint correct_diff = "98765432109876530865";
  // std::cout << num_a << " + " << num_b << " = " << diff_val << "\n";
  // std::cout << "Correct? " << (diff_val == correct_diff ? "Yes" : "No")
  //           << "\n\n";
  // std::cout << correct_diff << std::endl;

  // int arr1[] = {-2, -3, -1};
  // int arr2[] = {-1, 2, -5};
  // bigint a(arr1, 3);
  // std::cout << a << "\n";

  // bigint a = "8126547125476512645127645712654812748971628746128";
  // bigint b =
  // "19826487125647612576444444444444444444444444444444444576215476";
  //
  // bigint res = a * b;

  int arr1[] = {-2147483648, -1000000000};

  int arr2[] = {-1, -1000000000};

  bigint a(arr1, 2);
  bigint b(arr2, 2);

  std::cout << a << " + " << b << " = " << a + b << std::endl;

  return 0;
}
