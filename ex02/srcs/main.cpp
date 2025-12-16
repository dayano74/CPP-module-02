#include <iostream>

#include "../incs/Fixed.hpp"

int main(void) {
  {
    // Test case from subject
    Fixed a;
    Fixed const b(Fixed(5.05f) * Fixed(2));
    std::cout << a << std::endl;
    std::cout << ++a << std::endl;
    std::cout << a << std::endl;
    std::cout << a++ << std::endl;
    std::cout << a << std::endl;
    std::cout << b << std::endl;
    std::cout << Fixed::max(a, b) << std::endl;
  }


  // // ---------------- Additional Test Cases ----------------
  // std::cout << "\n=== Arithmetic operators ===" << std::endl;
  // Fixed x(10);    // int constructor
  // Fixed y(3.5f);  // float constructor
  // std::cout << "x = " << x << ", y = " << y << std::endl;
  // std::cout << "x + y = " << (x + y) << std::endl;
  // std::cout << "x - y = " << (x - y) << std::endl;
  // std::cout << "x * y = " << (x * y) << std::endl;
  // std::cout << "x / y = " << (x / y) << std::endl;

  // Fixed e(5.05f), f(2);
  // std::cout << "e = " << e << ", f = " << f << std::endl;
  // std::cout << "e / f = " << (e / f) << std::endl;  // check division

  // std::cout << "\n=== Increment / Decrement ===" << std::endl;
  // Fixed inc(1.5f);
  // std::cout << "start inc = " << inc << std::endl;
  // std::cout << "pre++ => " << ++inc << std::endl;                     // pre-increment
  // std::cout << "post++ => " << inc++ << " now " << inc << std::endl;  // post-increment
  // std::cout << "pre-- => " << --inc << std::endl;                     // pre-decrement
  // std::cout << "post-- => " << inc-- << " now " << inc << std::endl;  // post-decrement

  // std::cout << "\n=== Comparison operators ===" << std::endl;
  // std::cout << std::boolalpha;  // print bool as true/false
  // std::cout << "x > y  : " << (x > y) << std::endl;
  // std::cout << "x < y  : " << (x < y) << std::endl;
  // std::cout << "x >= y : " << (x >= y) << std::endl;
  // std::cout << "x <= y : " << (x <= y) << std::endl;
  // std::cout << "x == y : " << (x == y) << std::endl;
  // std::cout << "x != y : " << (x != y) << std::endl;

  // std::cout << "\n=== min / max (non-const) ===" << std::endl;
  // Fixed m1(42.25f), m2(42.24f);
  // std::cout << "m1 = " << m1 << ", m2 = " << m2 << std::endl;
  // std::cout << "min(m1, m2) = " << Fixed::min(m1, m2) << std::endl;
  // std::cout << "max(m1, m2) = " << Fixed::max(m1, m2) << std::endl;

  // std::cout << "\n=== min / max (const) ===" << std::endl;
  // const Fixed c1(-5.5f), c2(-10);
  // std::cout << "c1 = " << c1 << ", c2 = " << c2 << std::endl;
  // std::cout << "min(c1, c2) = " << Fixed::min(c1, c2) << std::endl;
  // std::cout << "max(c1, c2) = " << Fixed::max(c1, c2) << std::endl;

  // std::cout << "\n=== Precision edge (LSB check) ===" << std::endl;
  // // If fractional bits = 8, smallest step is 1/256 ≈ 0.00390625
  // Fixed one(1.0f);
  // Fixed lsb(0.00390625f);
  // std::cout << "one = " << one << ", lsb = " << lsb << std::endl;
  // std::cout << "one + lsb = " << (one + lsb) << std::endl;

  // std::cout << "\n=== Mixed expressions ===" << std::endl;
  // Fixed mix = ((x + y) * e) / f - m2;
  // std::cout << "((x + y) * e) / f - m2 = " << mix << std::endl;

  // std::cout << "\n=== Self comparison sanity ===" << std::endl;
  // std::cout << "x == x : " << (x == x) << std::endl;
  // std::cout << "x != x : " << (x != x) << std::endl;

  // // ------------------------------------------------------

  return 0;
}
