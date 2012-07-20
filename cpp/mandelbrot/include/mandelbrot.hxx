#ifndef MANDELBROT_HXX
#define MANDELBROT_HXX
#include <iostream>
#include "complex.hxx"
#include <vector>

class Mandelbrot {
private:
  double xmin_;
  double xmax_;
  double ymin_;
  double ymax_;
  int stepsX_;
  int stepsY_;
  int maxIter_;
public:
  Mandelbrot();
  Mandelbrot(double xmin,
	     double xmax,
	     double ymin,
	     double ymax,
	     int stepsX,
	     int stepsY,
	     int maxIter) :
    xmin_(xmin), xmax_(xmax), ymin_(ymin), ymax_(ymax),
    stepsX_(stepsX), stepsY_(stepsY), maxIter_(maxIter)
  {};

  void setCoord(double xmin, double xmax, double ymin, double ymax);
  void setSteps(double setpsX, double stepsY);
  void setIter(int maxIter);
  void fillGrid();
};
#endif
