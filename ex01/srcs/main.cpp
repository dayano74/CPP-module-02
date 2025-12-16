#include <cassert>
#include <cmath>
#include <iostream>

#include "../incs/Fixed.hpp"

// static bool nearlyEqual(float a, float b, float eps) {
//   return std::fabs(a - b) <= eps;
// }

int main(void) {
  {
    // サブジェクトのテストケース
    Fixed a;
    Fixed const b(10);
    Fixed const c(42.42f);
    Fixed const d(b);

    a = Fixed(1234.4321f);

    std::cout << "a is " << a << std::endl;
    std::cout << "b is " << b << std::endl;
    std::cout << "c is " << c << std::endl;
    std::cout << "d is " << d << std::endl;
    std::cout << "a is " << a.toInt() << " as integer" << std::endl;
    std::cout << "b is " << b.toInt() << " as integer" << std::endl;
    std::cout << "c is " << c.toInt() << " as integer" << std::endl;
    std::cout << "d is " << d.toInt() << " as integer" << std::endl;
  }

  // {
  //   // デフォルトコンストラクタは0で初期化されるか
  //   Fixed a;
  //   assert(a.getRawBits() == 0);
  //   assert(a.toInt() == 0);
  //   assert(a.toFloat() == 0.0f);
  // }

  // {
  //   // intコンストラクタがraw（<<8）・toInt・toFloatを正しく生成するか
  //   Fixed a(1);
  //   assert(a.getRawBits() == (1 << 8));
  //   assert(a.toInt() == 1);
  //   assert(a.toFloat() == 1.0f);

  //   Fixed b(-3);
  //   assert(b.getRawBits() == (-3 * 256));
  //   assert(b.toInt() == -3);
  //   assert(b.toFloat() == -3.0f);
  // }

  // {
  //   // floatコンストラクタの丸めとtoFloat/toIntの整合性（0.5/1.5/0.1）
  //   Fixed a(0.5f);
  //   assert(a.getRawBits() == 128);
  //   assert(a.toInt() == 0);
  //   assert(a.toFloat() == 0.5f);

  //   Fixed b(1.5f);
  //   assert(b.getRawBits() == 384);
  //   assert(b.toInt() == 1);
  //   assert(b.toFloat() == 1.5f);

  //   // 1/256 刻みでは正確に表現できない値の例: 0.1
  //   // 入力 float に対して「十分近いこと」をテストする（fixed の最小刻みの半分まで許容）
  //   Fixed c(0.1f);
  //   assert(nearlyEqual(c.toFloat(), 0.1f, 1.0f / 512.0f));
  // }

  // {
  //   // コピーコンストラクタ/代入でrawが一致し、独立性が維持されるか
  //   Fixed a(42.42f);
  //   Fixed b(a);
  //   Fixed c;
  //   c = a;

  //   assert(b.getRawBits() == a.getRawBits());
  //   assert(c.getRawBits() == a.getRawBits());
  //   assert(b.toFloat() == a.toFloat());
  //   assert(c.toFloat() == a.toFloat());

  //   b.setRawBits(0);
  //   assert(b.getRawBits() == 0);
  //   assert(a.getRawBits() != 0);
  // }

  // {
  //   // setRawBits/getRawBitsとtoFloatの整合性（raw/256）
  //   Fixed a;
  //   a.setRawBits(12345);
  //   assert(a.getRawBits() == 12345);

  //   assert(a.toFloat() == 12345.0f / 256.0f);
  // }

  // {
  //   // operator<< がコンパイルできて出力できるか
  //   Fixed a(2.5f);
  //   std::cout << "operator<< check: " << a << std::endl;
  // }

  // std::cout << "All ex01 tests passed.\n";
  return 0;
}
