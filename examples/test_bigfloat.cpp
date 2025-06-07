#include <cassert>
#include <exception>
#include <iostream>
#include <sstream>
#include <stdexcept>

#include "bigfloat.h"

int test_bigfloat() {
  std::cout << "===== Bigfloat Functionality Demonstration =====\n\n";

  try {
    // Test construction
    bigfloat a(1, 2);  // 1/2
    bigfloat b(3, 4);  // 3/4
    bigfloat c = 2;    // 2/1
    bigfloat d = b;    // Copy constructor
    bigfloat e = -a;   // -1/2

    std::cout << "a = " << a << " (1/2)\n";
    std::cout << "b = " << b << " (3/4)\n";
    std::cout << "c = " << c << " (2/1)\n";
    std::cout << "d (copy of b) = " << d << " (3/4)\n";
    std::cout << "e = -a = " << e << " (-1/2)\n\n";

    // Test arithmetic operations
    bigfloat sum = a + b;
    bigfloat diff = b - a;
    bigfloat prod = a * b;
    bigfloat quot = b / a;

    std::cout << "a + b = " << sum << " (5/4)\n";
    std::cout << "b - a = " << diff << " (1/4)\n";
    std::cout << "a * b = " << prod << " (3/8)\n";
    std::cout << "b / a = " << quot << " (3/2)\n\n";

    // Test comparisons
    std::cout << "a == 1/2? " << (a == bigfloat(1, 2)) << " (1)\n";
    std::cout << "a != b? " << (a != b) << " (1)\n";
    std::cout << "a < b? " << (a < b) << " (1)\n";
    std::cout << "b > a? " << (b > a) << " (1)\n";
    std::cout << "a <= 1/2? " << (a <= bigfloat(1, 2)) << " (1)\n";
    std::cout << "b >= 3/4? " << (b >= bigfloat(3, 4)) << " (1)\n\n";

    // Test fraction simplification
    bigfloat g(4, 6);
    bigfloat h(15, 25);
    std::cout << "4/6 simplified = " << g << " (2/3)\n";
    std::cout << "15/25 simplified = " << h << " (3/5)\n\n";

    // Test trigonometric functions with π/4 (45°)
    bigfloat eps = bigfloat(1, 1000000);  // 1e-6 precision
    bigfloat pi4 = bigfloat::PI(eps) / 4;

    std::cout
        << "Calculating trigonometric functions at π/4 (45°) with EPS=1e-6:\n";
    bigfloat s = sin(pi4, eps);
    bigfloat cs = cos(pi4, eps);
    bigfloat t = tg(pi4, eps);

    std::cout << "sin(π/4) ≈ " << s << " (expected ≈707107/1000000)\n";
    std::cout << "cos(π/4) ≈ " << cs << " (expected ≈707107/1000000)\n";
    std::cout << "tan(π/4) ≈ " << t << " (expected ≈1/1)\n";
    std::cout << "sin² + cos² ≈ " << (s * s + cs * cs)
              << " (expected ≈1/1)\n\n";

    // Test inverse trig functions
    bigfloat half(1, 2);
    bigfloat as = arcsin(half, eps);
    bigfloat ac = arccos(half, eps);
    bigfloat at = arctg(bigfloat(1), eps);  // arctan(1) = π/4

    std::cout << "arcsin(1/2) ≈ " << as << " (expected ≈π/6)\n";
    std::cout << "arccos(1/2) ≈ " << ac << " (expected ≈π/3)\n";
    std::cout << "arctan(1/1) ≈ " << at << " (expected ≈π/4)\n";
    std::cout << "arcsin(1/2) + arccos(1/2) ≈ " << (as + ac)
              << " (expected ≈π/2)\n\n";

    // Test exponential and logarithmic functions
    bigfloat sq = sqrt(bigfloat(2), eps);
    bigfloat lg = log2(bigfloat(8), eps);
    bigfloat ln = log(bigfloat::PI(eps), eps);
    bigfloat lg10 = log10(bigfloat(1000), eps);

    std::cout << "sqrt(2) ≈ " << sq << " (expected ≈1414214/1000000)\n";
    std::cout << "log2(8) ≈ " << lg << " (expected 3/1)\n";
    std::cout << "log(PI) ≈ " << ln << " (no simple fraction)\n";
    std::cout << "log10(1000) ≈ " << lg10 << " (expected 3/1)\n\n";

    // Test radical function
    bigfloat cube_root = radical(bigfloat(27), 3, eps);
    std::cout << "radical(27, 3) ≈ " << cube_root << " (expected 3/1)\n\n";

    // Test constants
    bigfloat pi_approx = bigfloat::PI(eps);
    std::cout << "PI ≈ " << pi_approx << " (expected ≈355/113)\n\n";

    // Test I/O operations
    bigfloat in1, in2;
    std::cout << "Enter two bigfloats in fraction form (a/b): ";
    std::cin >> in1 >> in2;
    std::cout << "You entered: " << in1 << " and " << in2 << "\n";
    std::cout << "Sum: " << (in1 + in2) << "\n";
    std::cout << "Product: " << (in1 * in2) << "\n\n";

    // Test edge cases
    std::cout << "Testing division by zero:\n";
    try {
      bigfloat zero(0);
      bigfloat res = a / zero;
      std::cout << "Division by zero succeeded (INCORRECT)\n";
    } catch (const std::exception& ex) {
      std::cout << "Caught exception: " << ex.what() << " (CORRECT)\n";
    }

    std::cout << "\nTesting zero denominator in constructor:\n";
    try {
      bigfloat invalid(1, 0);
      std::cout << "Created fraction with zero denominator (INCORRECT)\n";
    } catch (const std::exception& ex) {
      std::cout << "Caught exception: " << ex.what() << " (CORRECT)\n";
    }

    std::cout << "\n===== Demonstration Complete =====\n";
  } catch (const std::exception& e) {
    std::cout << "Unexpected exception: " << e.what() << "\n";
    return 1;
  }
  return 0;
}
