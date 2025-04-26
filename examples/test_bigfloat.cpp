#include <exception>
#include <iostream>

#include "bigfloat.h"

int test_bigfloat() {
  try {
    std::cout << "===== Bigfloat Functionality Demonstration =====\n\n";

    std::cout << "1. Constructors:\n";

    bigfloat a;
    bigint big_int("123456789");
    bigfloat b(big_int);
    bigfloat c(44, 14);
    bigfloat d(3, 52);
    bigfloat e = c;

    std::cout << "a (default): " << a << "\n";
    std::cout << "b (from bigint 12345): " << b << "\n";
    std::cout << "c (22/7): " << c << "\n";
    std::cout << "d (3/52): " << d << "\n";
    std::cout << "e (copy of c): " << e << "\n\n";

    std::cout << "2. Arithmetic operations:\n";
    bigfloat sum = c + d;
    bigfloat diff = c - d;
    bigfloat prod = c * d;
    bigfloat quot = c / d;

    std::cout << "c + d: " << sum << "\n";
    std::cout << "c - d: " << diff << "\n";
    std::cout << "c * d: " << prod << "\n";
    std::cout << "c / d: " << quot << "\n\n";

    std::cout << "3. Compound assignments:\n";
    bigfloat x(5);
    x += bigfloat(3);
    std::cout << "x += 3: " << x << "\n";
    x -= bigfloat(2);
    std::cout << "x -= 2: " << x << "\n";
    x *= bigfloat(4);
    std::cout << "x *= 4: " << x << "\n";
    x /= bigfloat(2);
    std::cout << "x /= 2: " << x << "\n\n";

    std::cout << "4. Comparisons:\n";
    std::cout << "c == e: " << (c == e) << "\n";
    std::cout << "c != d: " << (c != d) << "\n";
    std::cout << "c < d: " << (c < d) << "\n";
    std::cout << "c > d: " << (c > d) << "\n";
    std::cout << "c <= d: " << (c <= d) << "\n";
    std::cout << "c >= d: " << (c >= d) << "\n\n";

    std::cout << "5. Unary operations:\n";
    std::cout << "-c: " << -c << "\n";
    std::cout << "c.abs(): " << c.abs() << "\n";
    bigfloat neg = c;
    neg.negate();
    std::cout << "c.negate(): " << neg << "\n\n";

    std::cout << "7. Mathematical functions:\n";
    bigfloat eps(1, 100000000);

    std::cout << "sin(π/4): " << sin(bigfloat::PI(eps) / bigfloat(4), eps)
              << "\n";
    std::cout << "cos(π/4): " << cos(bigfloat::PI(eps) / bigfloat(4), eps)
              << "\n";
    std::cout << "tan(π/4): " << tg(bigfloat::PI(eps) / bigfloat(4), eps)
              << "\n";

    bigfloat two(2);
    std::cout << "2^10: " << pow(two, bigint(10)) << "\n";
    std::cout << "sqrt(2): " << sqrt(two, eps) << "\n";

    std::cout << "log2(8): " << log2(bigfloat(8), eps) << "\n";
    std::cout << "ln(PI): " << log(bigfloat::PI(eps), eps) << "\n";

    std::cout << "π: " << bigfloat::PI(eps) << "\n\n";

    std::cout << "8. Input/output:\n";
    bigfloat input;
    std::cout << "Enter a BigFloat (e.g. '3.14159' or '22/7'): ";
    std::cin >> input;
    std::cout << "You entered: " << input << "\n";

    std::cout << "\n===== Demonstration Complete =====\n";
  } catch (std::exception const &e) {
    std::cout << "exception catched during Demonstration of bigfloat\n";
  }
  return 0;
}
