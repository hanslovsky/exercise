#ifndef COMPLEX_HXX
#define COMPLEX_HXX
#include <iostream>


class Complex {
private:
  double x_, y_;
public:
  Complex() : x_(0), y_(0) {}
  Complex(double x, double y) :
    x_(x), y_(y)
  {};
  Complex(const Complex &c) :
    x_(c.x_), y_(c.y_)
  {};

  
  Complex add(const Complex &c) const;
  Complex sub(const Complex &c) const;
  Complex mult(const Complex &c) const;
  Complex div(const Complex &c) const;
  Complex addScalar(const double &scalar);

  static Complex add(const Complex &c1, const Complex &c2);
  static Complex sub(const Complex &c1, const Complex &c2);
  static Complex mult(const Complex &c1, const Complex &c2);
  static Complex div(const Complex &c1, const Complex &c2);
  
  void setR(double x);
  void setI(double y);
  void set(double x, double y);

  Complex conj() const;
  
  double getR() const;
  double getI() const;
  double sqAbs() const;
  double abs() const;

  
  Complex& operator=(const Complex &c);
  Complex operator-() const;
  
  friend Complex operator+(const Complex &c1, const Complex &c2);
  friend Complex operator-(const Complex &c1, const Complex &c2);
  friend Complex operator*(const Complex &c1, const Complex &c2);
  friend Complex operator/(const Complex &c1, const Complex &c2);

  friend Complex operator+(const Complex &c, const double &scalar);
  friend Complex operator-(const Complex &c, const double &scalar);
  friend Complex operator*(const Complex &c, const double &scalar);
  friend Complex operator/(const Complex &c, const double &scalar);

  friend Complex operator+(const double &scalar, const Complex &c);
  friend Complex operator-(const double &scalar, const Complex &c);
  friend Complex operator*(const double &scalar, const Complex &c);
  friend Complex operator/(const double &scalar, const Complex &c);
};

#endif /*COMPLEX_HXX*/

