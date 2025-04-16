#include <cassert>
#include <climits>
#include <iostream>
#include <ostream>

#include "bigint.h"

int main() {
  int arr[] = {-1, 0};
  bigint a = INT_MIN;
  bigint b = -1;
  std::cout << "INT_MIN - 1" << std::endl;
  std::cout << "In: " << a << " + " << b << std::endl;
  auto result = a + b;
  std::cout << "Out: " << result << std::endl;
  std::cout << "Err. Underflow with negatives adds -1 instead of 1."
            << std::endl
            << std::endl;

  a = INT_MAX;
  b = 1;
  std::cout << "INT_MAX + 1" << std::endl;
  std::cout << "In: " << a << " + " << b << std::endl;
  result = a + b;
  std::cout << "Out: " << result << std::endl;
  std::cout << "Ok." << std::endl << std::endl;

  a.from_array(arr, 2);
  b = 1;
  std::cout << "[-1, 0] + 1" << std::endl;
  std::cout << "In: " << a << " + " << b << std::endl;
  result = a + b;
  std::cout << "Out: " << result << std::endl;
  std::cout << "Ok." << std::endl << std::endl;

  a = -1;
  b = 1;
  std::cout << "-1 + 1" << std::endl;
  std::cout << "In: " << a << " + " << b << std::endl;
  result = a + b;
  std::cout << "Out: " << result << std::endl;
  std::cout << "Err. Should not overflow. Solve: remove extra 1." << std::endl
            << std::endl;

  a = 50;
  b = -2;
  std::cout << "50 - 2" << std::endl;
  std::cout << "In: " << a << " + " << b << std::endl;
  result = a + b;
  std::cout << "Out: " << result << std::endl;
  std::cout
      << "Err. Should not overflow. Solve: remove extra 1. Same as prev err"
      << std::endl
      << std::endl;

  a = 1000;
  b = -7;
  std::cout << "1000 - 7" << std::endl;
  std::cout << "In: " << a << " + " << b << std::endl;
  result = a + b;
  std::cout << "Out: " << result << std::endl;
  std::cout << "Err. Should not overflow. Solve: remove extra 1. Same as prev "
               "err, happens if b is "
               "negative and abs(a) > abs(b)"
            << std::endl
            << std::endl;

  a = 1000;
  b = -1007;
  std::cout << "1000 - 1007" << std::endl;
  std::cout << "In: " << a << " + " << b << std::endl;
  result = a + b;
  std::cout << "Out: " << result << std::endl;
  std::cout << "Err. Shouldn't contain extra 0. Solve: remove extra 0. Same as "
               "prev err, happens if b is "
               "negative and abs(a) < abs(b)."
            << std::endl
            << std::endl;

  a = -1000;
  b = -1007;
  std::cout << "In: " << a << " + " << b << std::endl;
  result = a + b;
  std::cout << "Out: " << result << std::endl;
  std::cout << "Err. Shouldn't contain extra 0. Solve: remove extra 0. Same as "
               "prev err, happens if b is "
               "negative and abs(a) < abs(b)."
            << std::endl
            << std::endl;

  std::cout << "======================" << std::endl;

  int arr2[] = {-1, -1};
  a.from_array(arr2, 2);
  b = -1;
  std::cout << a + b << std::endl;
}
