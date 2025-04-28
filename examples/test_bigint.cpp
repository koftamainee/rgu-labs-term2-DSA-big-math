#include <iostream>
#include <optional>

#include "bigint.h"

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
  bigint numerator = bigint::factorial(2 * n);
  bigint denominator = bigint::factorial(n + 1) * bigint::factorial(n);
  return numerator / denominator;
}

int test_bigint() {
  std::cout << "===== Bigint Functionality Demonstration =====\n\n";
  try {
    bigint num_a = 12345;
    bigint num_b = "98765432109876543210";
    bigint num_c = num_a;
    bigint num_d = std::move(num_c);

    std::cout << "num_a = " << num_a << "\n";
    std::cout << "num_b = " << num_b << "\n";
    std::cout << "num_d (moved from num_c) = " << num_d << "\n\n";

    bigint sum_val = num_a + num_b;
    bigint correct_sum = "98765432109876555555";
    std::cout << "num_a + num_b = " << sum_val << "\n";
    std::cout << "Correct? " << (sum_val == correct_sum ? "Yes" : "No")
              << "\n\n";

    bigint diff_val = num_b - num_a;
    bigint correct_diff = "98765432109876530865";
    std::cout << "num_b - num_a = " << diff_val << "\n";
    std::cout << "Correct? " << (diff_val == correct_diff ? "Yes" : "No")
              << "\n\n";

    bigint prod_val = num_a * num_b;
    bigint correct_prod = "1219259259396425925927450";
    std::cout << "num_a * num_b = " << prod_val << "\n";
    std::cout << "Correct? " << (prod_val == correct_prod ? "Yes" : "No")
              << "\n\n";

    auto division_result = bigint::division(num_b, num_a);
    bigint correct_quot = "8000440025101380";
    bigint correct_rem = "7110";
    std::cout << "num_b / num_a = " << division_result.quotient()
              << ", remainder = " << division_result.remainder() << "\n";
    std::cout << "Correct? "
              << (division_result.quotient() == correct_quot &&
                          division_result.remainder() == correct_rem
                      ? "Yes"
                      : "No")
              << "\n\n";

    std::cout << "trying to divide num_a by zero...\n";
    try {
      bigint zero_val = 0;
      auto invalid_div = bigint::division(num_a, zero_val);
      std::cout << "division by zero failed - exception not thrown!" << "\n\n";
    } catch (bigint::zero_division_exception &) {
      std::cout << "caught division by zero exception (correct behavior)"
                << "\n\n";
    }

    std::cout << "trying to divide zero by zero...\n";
    try {
      bigint zero_val = 0;
      auto invalid_div = bigint::division(zero_val, zero_val);
      std::cout << "division zero by zero failed - exception not thrown!"
                << "\n\n";
    } catch (bigint::mathematical_uncertainty_exception &) {
      std::cout
          << "caught mathematical uncertainty exception (correct behavior)"
          << "\n\n";
    }

    bigint inc_val = num_a;
    bigint correct_prefix = 12346;
    std::cout << "inc_val = " << ++inc_val << " (prefix)\n";
    std::cout << "Correct? " << (inc_val == correct_prefix ? "Yes" : "No")
              << "\n";

    bigint correct_postfix = 12346;
    std::cout << "inc_val++ = " << inc_val++ << ", now " << inc_val
              << " (postfix)\n";
    std::cout << "Correct? " << (inc_val == correct_postfix + 1 ? "Yes" : "No")
              << "\n\n";

    bigint neg_val = -num_a;
    bigint correct_neg = -12345;
    std::cout << "-num_a = " << neg_val << "\n";
    std::cout << "Correct? " << (neg_val == correct_neg ? "Yes" : "No") << "\n";

    bigint abs_val = neg_val.abs();
    std::cout << "abs(-num_a) = " << abs_val << "\n";
    std::cout << "Correct? " << (abs_val == num_a ? "Yes" : "No") << "\n\n";

    bigint bitwise1 = "255";
    bigint bitwise2 = "15";
    bigint correct_and = 15;
    std::cout << "bitwise1 & bitwise2 = " << (bitwise1 & bitwise2) << "\n";
    std::cout << "Correct? "
              << ((bitwise1 & bitwise2) == correct_and ? "Yes" : "No") << "\n";

    bigint correct_or = 255;
    std::cout << "bitwise1 | bitwise2 = " << (bitwise1 | bitwise2) << "\n";
    std::cout << "Correct? "
              << ((bitwise1 | bitwise2) == correct_or ? "Yes" : "No") << "\n";

    bigint correct_xor = 240;
    std::cout << "bitwise1 ^ bitwise2 = " << (bitwise1 ^ bitwise2) << "\n";
    std::cout << "Correct? "
              << ((bitwise1 ^ bitwise2) == correct_xor ? "Yes" : "No") << "\n";

    bigint correct_not = -16;
    std::cout << "~bitwise2 = " << (~bitwise2) << "\n";
    std::cout << "Correct? " << ((~bitwise2) == correct_not ? "Yes" : "No")
              << "\n";

    bigint correct_shift_left = 4080;
    std::cout << "bitwise1 << 4 = " << (bitwise1 << 4) << "\n";
    std::cout << "Correct? "
              << ((bitwise1 << 4) == correct_shift_left ? "Yes" : "No") << "\n";

    bigint correct_shift_right = 63;
    std::cout << "bitwise1 >> 2 = " << (bitwise1 >> 2) << "\n";
    std::cout << "Correct? "
              << ((bitwise1 >> 2) == correct_shift_right ? "Yes" : "No")
              << "\n\n";

    bool correct_lt = true;
    std::cout << "num_a < num_b: " << (num_a < num_b ? "true" : "false")
              << "\n";
    std::cout << "Correct? " << ((num_a < num_b) == correct_lt ? "Yes" : "No")
              << "\n";

    bool correct_ge = true;
    std::cout << "num_b >= num_a: " << (num_b >= num_a ? "true" : "false")
              << "\n";
    std::cout << "Correct? " << ((num_b >= num_a) == correct_ge ? "Yes" : "No")
              << "\n\n";

    int digits_array[] = {1, 2, 3, 4};
    bigint from_array_val;
    from_array_val.from_array(digits_array, 4);
    bigint correct_array_val = "316912650112397582603894390785";
    std::cout << "from_array_val = " << from_array_val << "\n";
    std::cout << "Correct? "
              << (from_array_val == correct_array_val ? "Yes" : "No") << "\n";

    bigint small_bigint = 5248;
    auto maybe_int = small_bigint.to_int();
    int correct_int = 5248;
    if (maybe_int) {
      std::cout << small_bigint << " to_int: " << maybe_int.value() << "\n";
      std::cout << "Correct? "
                << (maybe_int.value() == correct_int ? "Yes" : "No") << "\n\n";
    } else {
      std::cout << "to_int: value too large for int (incorrect behavior)\n\n";
    }

    std::cout << "Enter two large numbers separated by space: ";
    bigint x_val;
    bigint y_val;
    std::cin >> x_val >> y_val;
    std::cout << "You entered: x_val = " << x_val << ", y_val = " << y_val
              << "\n";
    std::cout << "x_val + y_val = " << (x_val + y_val) << "\n";
    std::cout << "Please verify these values manually\n\n";

    std::cout << "Testing very large computations:\n";

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

    bigint fact100 = bigint::factorial(10000);
    // std::cout << "Computing 100!:\n" << fact100 << "\n";
    // std::cout << "Correct? " << (fact100 == correct_fact100 ? "Yes" : "No")
    // << "\n\n";
    std::cout << "factorial computed\n";

    bigint fib1000 = fibonacci_iterative(10000);
    // std::cout << "Computing 1000th Fibonacci number:\n" << fib1000 << "\n";
    // std::cout << "Correct? " << (fib1000 == correct_fib1000 ? "Yes" : "No")
    // << "\n\n";

    bigint catalan100 = catalan_number(100);
    std::cout << "Computing Catalan(100):\n" << catalan100 << "\n";
    std::cout << "Correct? "
              << (catalan100 == correct_catalan100 ? "Yes" : "No") << "\n";

    std::cout << "\n===== Demonstration Complete =====\n";

  } catch (const std::exception &e) {
    std::cout << "Unexpected exception: " << e.what() << "\n";
    return 1;
  }
  return 0;
}
