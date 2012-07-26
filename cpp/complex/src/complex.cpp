#include <complex.hxx>
#include <iostream>
#include <cmath>

Complex Complex::add(const Complex &c) const {
  double re = x_ + c.getR();
  double im = y_ + c.getI();
  return Complex(re, im);
}

Complex Complex::sub(const Complex &c) const {
  return add(0+(-1.0*c));
}

Complex Complex::mult(const Complex &c) const {
  double re = x_*c.getR() - y_*c.getI();
  double im = x_*c.getI() + y_*c.getR();
  //std::cout << re << "  " << im << std::endl;
  return Complex(re, im);
}

Complex Complex::div(const Complex &c) const {
  Complex num = mult(c.conj());
  double den = c.sqAbs();
  den = den*den;
  return num/den;
}

Complex Complex::add(const Complex &c1, const Complex &c2) {
  return c1.add(c2);
}

Complex Complex::sub(const Complex &c1, const Complex &c2) {
  return c1.sub(c2);
}

Complex Complex::mult(const Complex &c1, const Complex &c2) {
  return c1.mult(c2);
}

Complex Complex::div(const Complex&c1, const Complex &c2) {
  return c1.div(c2);
}

void Complex::setR(double x) {
  x_ = x;
}

void Complex::setI(double y) {
  y_ = y;
}

void Complex::set(double x, double y) {
  setR(x);
  setI(y);
}

Complex Complex::conj() const {
  return Complex(x_, -y_);
}

double Complex::getR() const {
  return x_;
}

double Complex::getI() const {
  return y_;
}

double Complex::sqAbs() const {
  Complex prod = mult(conj());
  return prod.getR();
}

double Complex::abs() const {
  return std::sqrt(sqAbs());
}

/*Complex Complex::operator-() const{
  return Complex(-x_, -y_);
  }*/

Complex& Complex::operator=(const Complex &c) {
  if (this == &c)
    return *this;
  set(c.getR(), c.getI());
  return *this;
}

Complex Complex::operator-() const {
  return 0-*this;
}

Complex operator+(const Complex &c1, const Complex &c2) {
  return Complex::add(c1, c2);
}

Complex operator-(const Complex &c1, const Complex &c2) {
  return Complex::sub(c1, c2);
}

Complex operator*(const Complex &c1, const Complex &c2) {
  return Complex::mult(c1, c2);
}

Complex operator/(const Complex &c1, const Complex &c2) {
  return Complex::div(c1, c2);
}

Complex operator+(const Complex &c, const double &scalar) {
  return Complex(c.x_+scalar, c.y_+scalar);
}

Complex operator-(const Complex &c, const double &scalar) {
  return Complex(c.x_-scalar, c.y_-scalar);
}

Complex operator*(const Complex &c, const double &scalar) {
  return Complex(scalar*c.x_, scalar*c.y_);
}

Complex operator/(const Complex &c, const double &scalar) {
  return Complex(c.x_/scalar, c.y_/scalar);
}

Complex operator+(const double &scalar, const Complex &c) {
  return c+scalar;
}

Complex operator-(const double &scalar, const Complex &c) {
  return -c+scalar;
}
Complex operator*(const double &scalar, const Complex &c) {
  return c*scalar;
}

Complex operator/(const double &scalar, const Complex &c) {
  return Complex(scalar, 0)/c;
}
