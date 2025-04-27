#include <iostream>
#include <optional>

#include "bigint.h"

bigint factorial(bigint const &n) {
  if (n == 0) {
    return 1;
  }

  return n * factorial(n - 1);
}

bigint fibonacci_iterative(bigint const &n) {
  if (n <= 0) {
    return 0;
  }
  if (n == 1) {
    return 1;
  }

  bigint a = 0;
  bigint b = 1;
  bigint c;

  for (int i = 2; i <= n; ++i) {
    c = a + b;
    a = b;
    b = c;
  }

  return b;
}

int test_bigint() {
  std::cout << "===== Bigint Functionality Demonstration =====\n\n";
  try {
    bigint num_a(12345);
    bigint num_b("98765432109876543210");
    bigint num_c = num_a;
    bigint num_d = std::move(num_c);

    std::cout << "num_a = " << num_a << "\n";
    std::cout << "num_b = " << num_b << "\n";
    std::cout << "num_d (moved from num_c) = " << num_d << "\n\n";

    bigint sum_val = num_a + num_b;
    bigint diff_val = num_b - num_a;
    bigint prod_val = num_a * num_b;
    std::cout << "num_a + num_b = " << sum_val << "\n";
    std::cout << "num_b - num_a = " << diff_val << "\n";
    std::cout << "num_a * num_b = " << prod_val << "\n\n";

    auto division_result = bigint::division(num_b, num_a);
    std::cout << "num_b / num_a = " << division_result.quotient()
              << ", remainder = " << division_result.remainder() << "\n\n";

    try {
      bigint zero_val(0);
      auto invalid_div = bigint::division(num_a, zero_val);
      (void)invalid_div;
    } catch (bigint::zero_division_exception &) {
      std::cout << "Caught division by zero exception" << "\n\n";
    }

    bigint inc_val = num_a;
    std::cout << "inc_val = " << ++inc_val << " (prefix)\n";
    std::cout << "inc_val++ = " << inc_val++ << ", now " << inc_val
              << " (postfix)\n\n";

    bigint neg_val = -num_a;
    std::cout << "-num_a = " << neg_val << "\n";
    std::cout << "abs(-num_a) = " << neg_val.abs() << "\n\n";

    bigint bitwise1("255");
    bigint bitwise2("15");
    std::cout << "bitwise1 & bitwise2 = " << (bitwise1 & bitwise2) << "\n";
    std::cout << "bitwise1 | bitwise2 = " << (bitwise1 | bitwise2) << "\n";
    std::cout << "bitwise1 ^ bitwise2 = " << (bitwise1 ^ bitwise2) << "\n";
    std::cout << "~bitwise2 = " << (~bitwise2) << "\n";
    std::cout << "bitwise1 << 4 = " << (bitwise1 << 4) << "\n";
    std::cout << "bitwise1 >> 2 = " << (bitwise1 >> 2) << "\n\n";

    if (num_a < num_b) {
      std::cout << "num_a < num_b" << "\n";
    }
    if (num_b >= num_a) {
      std::cout << "num_b >= num_a" << "\n\n";
    }

    int digits_array[] = {1, 2, 3, 4};
    bigint from_array_val;
    from_array_val.from_array(digits_array, 4);
    std::cout << "from_array_val = " << from_array_val << "\n";

    auto maybe_int = from_array_val.to_int();
    if (maybe_int) {
      std::cout << "to_int: " << maybe_int.value() << "\n";
    } else {
      std::cout << "to_int: value too large for int" << "\n\n";
    }

    std::cout << "Enter two large numbers separated by space: ";
    bigint x_val;
    bigint y_val;
    std::cin >> x_val >> y_val;
    std::cout << "You entered: x_val = " << x_val << ", y_val = " << y_val
              << "\n";
    std::cout << "x_val + y_val = " << (x_val + y_val) << "\n";

    std::cout << "Testing very large computations: \n\n";
    std::cout << "Computing 100!: " << factorial(100) << std::endl;
    std::cout << "Computing 1000 Fibonacci number: ";
    bigint result = fibonacci_iterative(1000);
    std::cout << result << std::endl;

  } catch (const std::exception &e) {
    std::cout << "Unexpected exception: " << e.what() << "\n";
  }
  return 0;
}
