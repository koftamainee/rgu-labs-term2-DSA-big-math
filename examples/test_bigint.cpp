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

bigint catalan_number(int n) {
  bigint numerator = factorial(2 * n);
  bigint denominator = factorial(n + 1) * factorial(n);
  return numerator / denominator;
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

    std::cout << "\nTesting very large computations:\n";

    bigint correct_fact100 =
        "9332621544394415268169923885626670049071596826438162146859296389521759"
        "9993229915608941463976156518286253697920827223758251185210916864000000"
        "000000000000000000";
    bigint correct_fib1000 =
        "4346655768693745643568852767504062580256466051737178040248172908953655"
        "5417949051890403879840079255169295922593080322634775209689623239873322"
        "471161642996440906533187938298969649928516003704476137795166849228875";
    bigint correct_catalan100 =
        "896519947090131496687170070074100632420837521538745909320";

    bigint fact100 = factorial(100);
    std::cout << "Computing 100!:\n" << fact100 << "\n";
    std::cout << "Correct? " << (fact100 == correct_fact100 ? "Yes" : "No")
              << "\n\n";

    bigint fib1000 = fibonacci_iterative(1000);
    std::cout << "Computing 1000th Fibonacci number:\n" << fib1000 << "\n";
    std::cout << "Correct? " << (fib1000 == correct_fib1000 ? "Yes" : "No")
              << "\n\n";

    bigint catalan100 = catalan_number(100);
    std::cout << "Computing Catalan(100):\n" << catalan100 << "\n";
    std::cout << "Correct? "
              << (catalan100 == correct_catalan100 ? "Yes" : "No") << "\n";

    std::cout << "\n===== Demonstration Complete =====\n";

  } catch (const std::exception &e) {
    std::cout << "Unexpected exception: " << e.what() << "\n";
  }
  return 0;
}
