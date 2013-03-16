#include <boost/python.hpp>

#include "../include/complex.hxx"


using namespace boost::python;

Complex (Complex::*a)(const Complex&) const = &Complex::add;
Complex (Complex::*s)(const Complex&) const = &Complex::sub;
Complex (Complex::*m)(const Complex&) const = &Complex::mult;
Complex (Complex::*d)(const Complex&) const = &Complex::div;


void export_complex() {
  class_<Complex>("Complex")
    .def(init<double, double>(args("re", "im")))
    .def(init<Complex>(args("c")))
    .def("add", a)
    .def("sub", s)
    .def("mult", m)
    .def("div", d)
    .def("setR", &Complex::setR)
    .def("setI", &Complex::setI)
    .def("set", &Complex::set)
    .def("conj", &Complex::conj)
    .def("re", &Complex::getR)
    .def("im", &Complex::getI)
    .def("sqAbs", &Complex::sqAbs)
    .def("abs", &Complex::abs)
    ;
}

