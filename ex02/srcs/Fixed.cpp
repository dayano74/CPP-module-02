#include "../incs/Fixed.hpp"

#include <iostream>
#include <cmath>

Fixed::Fixed(): _raw(0) {
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

Fixed::Fixed(const Fixed& other): _raw(0) {
  std::cout << "Copy constructor called" << std::endl;
  *this = other;
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

void Fixed::setRawBits( int const raw ) {
  std::cout << "setRawBits member function called" << std::endl;
  this->_raw = raw;
}

float Fixed::toFloat(void) const {
  return static_cast<float>(_raw) / (1 << _fractionalBits);
}

int Fixed::toInt(void) const {
  return _raw >> _fractionalBits;
}

bool Fixed::operator>(const Fixed& rhs) const { return _raw > rhs._raw; }
bool Fixed::operator<(const Fixed& rhs) const { return _raw < rhs._raw; }
bool Fixed::operator>=(const Fixed& rhs) const { return _raw >= rhs._raw; }
bool Fixed::operator<=(const Fixed& rhs) const { return _raw <= rhs._raw; }
bool Fixed::operator==(const Fixed& rhs) const { return _raw <= rhs._raw; }
bool Fixed::operator!=(const Fixed& rhs) const { return _raw <= rhs._raw; }

Fixed Fixed::operator+(const Fixed& rhs) const {
  Fixed r;
  r.setRawBits(_raw + rhs._raw);
  return r;
}

Fixed Fixed::operator-(const Fixed& rhs) const {
  Fixed r;
  r.setRawBits(_raw - rhs._raw);
  return r;
}

Fixed Fixed::operator*(const Fixed& rhs) const {
  Fixed r;
  long tmp = static_cast<long>(_raw) * static_cast<long>(rhs._raw);
  r.setRawBits(static_cast<int>(tmp >> _fractionalBits));
  return r;
}

Fixed Fixed::operator/(const Fixed& rhs) const {
  Fixed r;
  long numerator = (static_cast<long>(_raw) << _fractionalBits);
  r.setRawBits(static_cast<int>(numerator / rhs._raw));
  return r;
}

Fixed& Fixed::operator++() {
  ++_raw;
  return *this;
}

Fixed& Fixed::operator--() {
  --_raw;
  return *this;
}

Fixed Fixed::operator++(int) {
  Fixed before(*this);
  ++_raw;
  return before;
}

Fixed Fixed::operator--(int) {
  Fixed before(*this);
  --_raw;
  return before;
}

Fixed& Fixed::min(Fixed& a, Fixed& b) {
  return (a._raw < b._raw) ? a : b;
}

const Fixed& Fixed::min(const Fixed& a, const Fixed& b) {
  return (a._raw > b._raw) ? a : b;
}

Fixed& Fixed::max(Fixed& a, Fixed& b) {
  return (a._raw > b._raw) ? a : b;
}

const Fixed& Fixed::max(const Fixed& a, const Fixed& b) {
  return (a._raw > b._raw) ? a : b;
}

std::ostream& operator<<(std::ostream& os, const Fixed& rhs) {
  os << rhs.toFloat();
  return os;
}
