#include <boost/python.hpp>

#include "../include/complex.hxx"


using namespace boost::python;

class Compl {
private:
  double re_;
  double im_;
public:
  Compl() : re_(0), im_(0) {}
  Compl(double re, double im) : re_(re), im_(im) {}

  double abs() {return re_*re_ + im_*im_;}
};

void export_complex() {
  class_<Complex>("Complex", init<>())
    .def(init<double, double>(args("re", "im")))
    .def("abs", &Complex::abs)
    ;
}
