#include <chrono>

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
//   std::cout << "Testing Karatsuba thresholds from " << min_threshold << " to
//   "
//             << max_threshold << " with step " << step << "\n";
//   std::cout << "Calculating factorials for each case...\n\n";
//   std::cout << "Threshold\tTime (ms)\n";
//   std::cout << "-----------------------" << std::endl;
//
//   for (int threshold = min_threshold; threshold <= max_threshold;
//        threshold += step) {
//     bigint::KARATSUBA_THRESHOLD = threshold;
//     std::cout << threshold;
//     std::cout.flush();
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
//     std::cout << "\t\t" << duration << "\n";
//   }
// }

int main() {
  // benchmark_karatsuba_threshold();
  // bigint_performance();
  test_bigint();
  // int arr[] = {1, 2, 3, 4};
  // bigint a(arr, 4);
  // bigint b = 15;
  // std::cout << a << " * " << b << std::endl;
  // std::cout << a * b << std::endl;
}
