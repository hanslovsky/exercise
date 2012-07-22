#include <iostream>
#include "include/complex.hxx"
#include "include/mandelbrot.hxx"

using namespace std;

int main() {
  Complex a(3, 4);
  Complex b(1, 1);
  Complex c(1, -1);
  // Complex d = b*3.0;
  Complex e(1, 0);
  Complex f(e.mult(e));
  e = e*e;
  //f = e.mult(e);
  cout << f.getR() << " " << f.getI() << endl;
  // cout << d.abs() << endl;
  

  Mandelbrot brot(-0.72, -0.7, 0.24, 0.26, 1000, 1000, 1000);
  brot.fillGrid();
  brot.writeToFile("mandelbrot.csv");
  return 0;
}
