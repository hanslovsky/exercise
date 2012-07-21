#include <iostream>
#include "include/complex.hxx"
#include "include/mandelbrot.hxx"

using namespace std;

int main() {
  Complex a(3, 4);
  cout << a.abs() << endl;
  Complex b(1, 1);
  Complex c(1, -1);
  Complex d = b*3.0;
  cout << d.abs() << endl;
  Mandelbrot brot;
  brot.fillGrid();
  return 0;
}
