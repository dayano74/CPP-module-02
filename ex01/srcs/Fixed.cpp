#include "../incs/Fixed.hpp"

#include <cmath>
#include <iostream>

Fixed::Fixed()
    : _raw(0) {
  std::cout << "Default constructor called" << std::endl;
}

Fixed::Fixed(const int value) {
  std::cout << "Int constructor called" << std::endl;
  _raw = value << _fractionalBits;
}

Fixed::Fixed(const float value) {
  std::cout << "float constructor called" << std::endl;
  _raw = static_cast<int>(roundf(value * (1 << _fractionalBits)));
}

Fixed::Fixed(const Fixed& other)
    : _raw(other._raw) {
  std::cout << "Copy constructor called" << std::endl;
}

Fixed& Fixed::operator=(const Fixed& rhs) {
  std::cout << "Copy assignment operator called" << std::endl;
  if (this != &rhs) {
    this->_raw = rhs._raw;
  }
  return *this;
}

Fixed::~Fixed() {
  std::cout << "Destructor called" << std::endl;
}

int Fixed::getRawBits() const {
  std::cout << "getRawBits member function called" << std::endl;
  return this->_raw;
}

void Fixed::setRawBits(int const raw) {
  std::cout << "setRawBits member function called" << std::endl;
  this->_raw = raw;
}

float Fixed::toFloat(void) const {
  return static_cast<float>(_raw) / (1 << _fractionalBits);
}

int Fixed::toInt(void) const {
  return _raw >> _fractionalBits;
}

std::ostream& operator<<(std::ostream& os, const Fixed& rhs) {
  os << rhs.toFloat();
  return os;
}
