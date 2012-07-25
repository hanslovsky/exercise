#ifndef MANDELBROT_HXX
#define MANDELBROT_HXX
#include <iostream>
#include "complex.hxx"
#include <vector>
#include <vigra/impex.hxx>

class Mandelbrot {
private:
  double xmin_;
  double xmax_;
  double ymin_;
  double ymax_;
  int stepsX_;
  int stepsY_;
  int maxIter_;
  Complex offset_;
  uint enhance_;
  vigra::BImage *grid_;
public:
  Mandelbrot() :
    xmin_(0.26), xmax_(0.27), ymin_(0), ymax_(0.01),
    stepsX_(100), stepsY_(100), maxIter_(1000),
    offset_(Complex(0,0)), enhance_(1), grid_(0)
    
  {};
  Mandelbrot(double xmin,
	     double xmax,
	     double ymin,
	     double ymax,
	     int stepsX,
	     int stepsY,
	     int maxIter,
	     Complex offset,
	     uint enhance) :
    xmin_(xmin), xmax_(xmax), ymin_(ymin), ymax_(ymax),
    stepsX_(stepsX), stepsY_(stepsY), maxIter_(maxIter),
    offset_(offset), enhance_(enhance), grid_(0)
  {};
  ~Mandelbrot();

  void setCoord(double xmin, double xmax, double ymin, double ymax);
  void setSteps(int stepsX, int stepsY);
  void setIter(int maxIter);
  void setEnhance(uint enhance);
  void fillGrid();
  bool writeToFile(const char *filename) const;
  bool writeImage(const char *filename) const;
};
#endif
