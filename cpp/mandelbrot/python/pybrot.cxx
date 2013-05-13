// define PY_ARRAY_UNIQUE_SYMBOL (required by the numpy C-API)
#define PY_ARRAY_UNIQUE_SYMBOL brot_pyarray

// boost
#include <boost/python.hpp>

// vigra
#include <vigra/numpy_array.hxx>
#include <vigra/numpy_array_converters.hxx>

void export_complex();
void export_mandelbrot();


BOOST_PYTHON_MODULE_INIT(mandelbrot) {
  vigra::import_vigranumpy();
  export_complex();
  export_mandelbrot();
}
