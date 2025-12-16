#include <iostream>
#include <cassert>

#include "../incs/Fixed.hpp"

int main(void) {
  {
  // Test case from ex00 subject
  Fixed a;
  Fixed b(a);
  Fixed c;

  c = b;

  std::cout << a.getRawBits() << std::endl;
  std::cout << b.getRawBits() << std::endl;
  std::cout << c.getRawBits() << std::endl;
  }

  {
    Fixed a;
    assert(a.getRawBits() == 0);
  }

  {
    Fixed a;
    a.setRawBits(123);

    Fixed b(a);
    Fixed c;
    c = a;

    assert(a.getRawBits() == 123);
    assert(b.getRawBits() == 123);
    assert(c.getRawBits() == 123);

    b.setRawBits(42);
    assert(a.getRawBits() == 123);
    assert(b.getRawBits() == 42);
    assert(c.getRawBits() == 123);
  }

  
  std::cout << "Tests passed.\n";
  return 0;
}
