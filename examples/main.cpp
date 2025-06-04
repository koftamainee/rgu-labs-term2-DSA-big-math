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
    int arr2[] = {2147483647, 1000000000};
    bigint a(arr1, 2);
    bigint b(arr2, 2);
    b.negate();
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
  test_bigint();
  // test_bigfloat();

  // test_bigint_addition();

  // bigint a = "78126478612475127645126547251547124";
  // bigint b = "418724638726478236478263784623";
  // b.negate();
  // std::cout << a << " + " << b << " = " << a + b << std::endl;

  // int arr[] = {-1, -1, -1, -15};
  // bigint a(arr, 4);
  // std::cout << a + 1 << std::endl;

  // bigint a = INT_MIN;
  // std::cout << a << " - 1 = " << a + (-1) << std::endl;

  // test_bigint_addition();

  bigint a =
      "716287436176254761254376812537651276351876537612548751732985723087356";
  bigint b =
      "2983471982637812673962173612876547812576451287645187245817625486715";
  bigint res =
      "713303964193616948580414638924774728539300086324903564487168097600641";

  std::cout << a << " - " << b << " = " << a - b << std::endl;
  std::cout << a - b << std::endl;
  std::cout << res << std::endl;

  return 0;
}
