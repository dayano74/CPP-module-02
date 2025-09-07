#ifndef FIXED_HPP
#define FIXED_HPP

class Fixed
{
private:
  int _raw;
  static const int _fractionalBits = 8;

public:
  Fixed();
  Fixed(const Fixed& other);
  Fixed& operator=(const Fixed&);
  ~Fixed();

  int getRawBits() const;
  void setRawBits( int const raw );
};



#endif  // FIXED_HPP
