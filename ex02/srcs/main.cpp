#include <cassert>
#include <iostream>

#include "../incs/Fixed.hpp"

int main(void) {
  // ===== 課題のテストケース =====
  {
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

  // // ===== 比較演算子のテスト =====
  // {
  //   Fixed a(10);
  //   Fixed b(5);
  //   Fixed c(10);
  //   Fixed neg(-3);
  //   Fixed zero(0);

  //   assert(a > b);
  //   assert(!(b > a));
  //   assert(!(a > c));
  //   assert(a > neg);
  //   assert(zero > neg);

  //   assert(b < a);
  //   assert(!(a < b));
  //   assert(!(a < c));
  //   assert(neg < a);
  //   assert(neg < zero);

  //   assert(a >= b);
  //   assert(a >= c);
  //   assert(!(b >= a));
  //   assert(zero >= zero);

  //   assert(b <= a);
  //   assert(a <= c);
  //   assert(!(a <= b));
  //   assert(zero <= zero);

  //   assert(a == c);
  //   assert(!(a == b));
  //   assert(zero == Fixed(0));

  //   assert(a != b);
  //   assert(!(a != c));
  //   assert(neg != zero);
  // }

  // // ===== 浮動小数点値での比較 =====
  // {
  //   Fixed a(5.5f);
  //   Fixed b(5.25f);
  //   Fixed c(5.5f);

  //   assert(a > b);
  //   assert(b < a);
  //   assert(a >= c);
  //   assert(a <= c);
  //   assert(a == c);
  //   assert(a != b);
  // }

  // // ===== 算術演算子のテスト =====
  // {
  //   Fixed a(10);
  //   Fixed b(5);

  //   Fixed sum = a + b;
  //   assert(sum.toInt() == 15);

  //   Fixed diff = a - b;
  //   assert(diff.toInt() == 5);

  //   Fixed prod = a * b;
  //   assert(prod.toInt() == 50);

  //   Fixed quot = a / b;
  //   assert(quot.toInt() == 2);
  // }

  // // ===== 浮動小数点値での算術演算 =====
  // {
  //   Fixed a(5.5f);
  //   Fixed b(2.0f);

  //   Fixed sum = a + b;
  //   assert(sum.getRawBits() == Fixed(7.5f).getRawBits());

  //   Fixed diff = a - b;
  //   assert(diff.getRawBits() == Fixed(3.5f).getRawBits());

  //   Fixed prod = a * b;
  //   assert(prod.getRawBits() == Fixed(11.0f).getRawBits());

  //   Fixed quot = a / b;
  //   assert(quot.getRawBits() == Fixed(2.75f).getRawBits());
  // }

  // // ===== 負の値での算術演算 =====
  // {
  //   Fixed a(10);
  //   Fixed b(-3);

  //   Fixed sum = a + b;
  //   assert(sum.toInt() == 7);

  //   Fixed diff = a - b;
  //   assert(diff.toInt() == 13);

  //   Fixed prod = a * b;
  //   assert(prod.toInt() == -30);

  //   Fixed quot = a / b;
  //   assert(quot < Fixed(0));
  //   assert(quot > Fixed(-4));
  // }

  // // ===== ゼロとの算術演算 =====
  // {
  //   Fixed a(10);
  //   Fixed zero(0);

  //   assert((a + zero).toInt() == 10);
  //   assert((a - zero).toInt() == 10);
  //   assert((a * zero).toInt() == 0);
  //   assert((zero / a).toInt() == 0);
  // }

  // // ===== インクリメント/デクリメント演算子のテスト =====
  // {
  //   Fixed epsilon;
  //   epsilon.setRawBits(1);

  //   // Pre-increment
  //   {
  //     Fixed a(0);
  //     Fixed& ref = ++a;
  //     assert(a.getRawBits() == 1);
  //     assert(&ref == &a);
  //     assert(a == epsilon);
  //   }

  //   // Post-increment
  //   {
  //     Fixed a(0);
  //     Fixed before = a++;
  //     assert(before.getRawBits() == 0);
  //     assert(a.getRawBits() == 1);
  //   }

  //   // Pre-decrement
  //   {
  //     Fixed a(0);
  //     Fixed& ref = --a;
  //     assert(a.getRawBits() == -1);
  //     assert(&ref == &a);
  //   }

  //   // Post-decrement
  //   {
  //     Fixed a(0);
  //     Fixed before = a--;
  //     assert(before.getRawBits() == 0);
  //     assert(a.getRawBits() == -1);
  //   }

  //   // Multiple increments
  //   {
  //     Fixed a(0);
  //     ++a;
  //     ++a;
  //     ++a;
  //     assert(a.getRawBits() == 3);
  //   }

  //   // Verify: 1 + epsilon > 1
  //   {
  //     Fixed one(1);
  //     Fixed oneAndEpsilon = one;
  //     ++oneAndEpsilon;
  //     assert(oneAndEpsilon > one);
  //   }
  // }

  // // ===== min/max 静的関数のテスト =====
  // {
  //   Fixed a(10);
  //   Fixed b(5);

  //   assert(&Fixed::min(a, b) == &b);
  //   assert(&Fixed::min(b, a) == &b);

  //   assert(&Fixed::max(a, b) == &a);
  //   assert(&Fixed::max(b, a) == &a);

  //   Fixed c(10);
  //   Fixed& minRef = Fixed::min(a, c);
  //   assert(minRef.toInt() == 10);

  //   Fixed& maxRef = Fixed::max(a, c);
  //   assert(maxRef.toInt() == 10);
  // }

  // // ===== min/max const参照版 =====
  // {
  //   const Fixed ca(10);
  //   const Fixed cb(5);

  //   assert(&Fixed::min(ca, cb) == &cb);
  //   assert(&Fixed::min(cb, ca) == &cb);

  //   assert(&Fixed::max(ca, cb) == &ca);
  //   assert(&Fixed::max(cb, ca) == &ca);
  // }

  // // ===== min/max 負の値 =====
  // {
  //   Fixed pos(5);
  //   Fixed neg(-5);
  //   Fixed zero(0);

  //   assert(&Fixed::min(pos, neg) == &neg);
  //   assert(&Fixed::max(pos, neg) == &pos);
  //   assert(&Fixed::min(zero, neg) == &neg);
  //   assert(&Fixed::max(zero, pos) == &pos);
  // }

  // // ===== min/max 浮動小数点値 =====
  // {
  //   Fixed a(3.14f);
  //   Fixed b(2.71f);

  //   assert(&Fixed::min(a, b) == &b);
  //   assert(&Fixed::max(a, b) == &a);
  // }

  // std::cout << "All tests passed!" << std::endl;
  return 0;
}
