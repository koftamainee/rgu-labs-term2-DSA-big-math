#include <chrono>
#include <climits>
#include <fstream>
#include <iomanip>

#include "bigint.h"

void test_bigint_addition() {
  std::cout << "=== Testing bigint addition ===" << std::endl;

  // Test 1: Adding two negative numbers
  {
    int arr1[] = {-2147483648, -1000000000};
    int arr2[] = {-1, -1000000000};
    bigint a(arr1, 2);
    bigint b(arr2, 2);
    bigint result = a + b;
    std::cout << "Test 1: " << a << " + " << b << " = " << result << std::endl;
  }

  // Test 2: Adding positive and negative numbers
  {
    int arr1[] = {2147483647, 1000000000};
    int arr2[] = {-1, -1000000000};
    bigint a(arr1, 2);
    bigint b(arr2, 2);
    bigint result = a + b;
    std::cout << "Test 2: " << a << " + " << b << " = " << result << std::endl;
  }

  // Test 3: Adding with zero
  {
    int arr1[] = {2147483647, 1000000000};
    int arr2[] = {0};
    bigint a(arr1, 2);
    bigint b(arr2, 1);
    bigint result = a + b;
    std::cout << "Test 3: " << a << " + " << b << " = " << result << std::endl;
  }

  // Test 4: Adding two large positive numbers
  {
    int arr1[] = {2147483647, 2147483647};
    int arr2[] = {1, 0};
    bigint a(arr1, 2);
    bigint b(arr2, 2);
    bigint result = a + b;
    std::cout << "Test 4: " << a << " + " << b << " = " << result << std::endl;
  }

  // Test 5: Adding with carry over multiple digits
  {
    int arr1[] = {2147483647, 2147483647, 2147483647};
    int arr2[] = {1, 0, 0};
    bigint a(arr1, 3);
    bigint b(arr2, 3);
    bigint result = a + b;
    std::cout << "Test 5: " << a << " + " << b << " = " << result << std::endl;
  }

  // Test 6: Adding numbers of different lengths
  {
    int arr1[] = {2147483647, 2147483647};
    int arr2[] = {1};
    bigint a(arr1, 2);
    bigint b(arr2, 1);
    bigint result = a + b;
    std::cout << "Test 6: " << a << " + " << b << " = " << result << std::endl;
  }

  // Test 7: Adding with the most negative number
  {
    int arr1[] = {-2147483648};
    int arr2[] = {-2147483648};
    bigint a(arr1, 1);
    bigint b(arr2, 1);
    bigint result = a + b;
    std::cout << "Test 7: " << a << " + " << b << " = " << result << std::endl;
  }

  // Test 8: Adding a positive number with its negative counterpart
  {
    int arr1[] = {2147483647, 1000000000};
    int arr2[] = {-2147483647, -1000000000};
    bigint a(arr1, 2);
    bigint b(arr2, 2);
    bigint result = a + b;
    std::cout << "Test 8: " << a << " + " << b << " = " << result << std::endl;
  }

  // Test 9: Adding with one
  {
    int arr1[] = {-2147483648};
    int arr2[] = {1};
    bigint a(arr1, 1);
    bigint b(arr2, 1);
    bigint result = a + b;
    std::cout << "Test 9: " << a << " + " << b << " = " << result << std::endl;
  }

  // Test 10: Adding with overflow and subsequent carry
  {
    int arr1[] = {-1, -1};
    int arr2[] = {-1, -1};
    bigint a(arr1, 2);
    bigint b(arr2, 2);
    bigint result = a + b;
    std::cout << "Test 10: " << a << " + " << b << " = " << result << std::endl;
  }

  std::cout << "=== Addition tests completed ===" << std::endl;
}

int test_bigint();
int test_bigfloat();
int bigint_performance();

bigint fibonacci_iterative(bigint const &n);

int main() {
  // benchmark_karatsuba_threshold();
  // bigint_performance();
  // test_bigint();

  // bigint a = INT_MIN;
  // std::cout << a << " - 1 = " << a + (-1) << std::endl;

  // test_bigint_addition();

  int arr[] = {-450461974, 1520782648, 5};
  bigint a(arr, 3);
  bigint b = 12345;

  bigint result = a / b;
  // int arr1[] = {1461013815, 1};
  // int arr2[] = {-1058799616, 0};
  //
  // bigint a(arr1, 2);
  // bigint b(arr2, 2);
  // b.negate();
  //
  // bigint res = a + b;
  // std::cout << a << " + " << b << " = " << res << "\n";

  return 0;
}
