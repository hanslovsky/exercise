#include <boost/python.hpp>

void export_complex();
// void export_mandelbrot();


BOOST_PYTHON_MODULE(mandelbrot) {
  export_complex();
  //export_mandelbrot();
}
