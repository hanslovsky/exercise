#include <iostream>
#include <complex.hxx>
#include <mandelbrot.hxx>
#include <own/parser.hxx>

using namespace std;

int main(int argc, char** argv) {
  Parser prs(argc, argv);
  int exit = prs.parseOptions();
  if (exit)
    throw exit;
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
  
  Complex offset(0,0);
  Mandelbrot brot(-0.72, -0.7, 0.24, 0.26, 100, 100, 1000, offset, 4);
  try {
    brot.fillGrid();
  }
  catch(...) {
    cout << "enhance < 1\n";
  }
  brot.writeImage("test.png");
  return 0;
}
