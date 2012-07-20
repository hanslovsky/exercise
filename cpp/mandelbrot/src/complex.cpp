#include "../include/complex.hxx"
#include <iostream>
#include <cmath>

Complex Complex::add(const Complex &c) const {
  double re = x_ + c.getR();
  double im = y_ + c.getI();
  return Complex(re, im);
}

Complex Complex::sub(const Complex &c) const {
  return add(-c);
}

Complex Complex::mult(const Complex &c) const {
  double re = x_*c.getR() - y_*c.getI();
  double im = y_*c.getI() - x_*c.getR();
  return Complex(re, im);
}

Complex Complex::div(const Complex &c) const {
  Complex num = mult(c.conj());
  double den = c.abs();
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

double Complex::abs() const {
  Complex prod = mult(conj());
  return std::sqrt(prod.getR());
}

Complex Complex::operator-() const{
  return Complex(-x_, -y_);
}

Complex Complex::operator=(const Complex &c) const {
  return c;
}

Complex Complex::operator+(const Complex &c) const {
  return add(c);
}

Complex Complex::operator-(const Complex &c) const {
  return sub(c);
}

Complex Complex::operator*(const Complex &c) const {
  return mult(c);
}

Complex Complex::operator/(const Complex &c) const {
  return div(c);
}

Complex Complex::operator*(const double &scalar) const {
  return Complex(scalar*x_, scalar*y_);
}

Complex Complex::operator/(const double &scalar) const {
  return Complex(x_/scalar, y_/scalar);
}
