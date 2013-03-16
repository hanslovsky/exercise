#ifndef MANDELBROT_HXX
#define MANDELBROT_HXX

// stl
#include <iostream>

//vigra
#include <vector>
#include <vigra/impex.hxx>
#include <vigra/multi_array.hxx>
#include <vigra/multi_iterator.hxx>

// own
#include "complex.hxx"

typedef unsigned short ushort;
typedef vigra::MultiArray<2, ushort>::traverser Iterator2D;
typedef vigra::StridedMultiIterator<1, ushort> Iterator1D;


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
  vigra::MultiArray<2, ushort> grid_;
public:
  Mandelbrot() :
    xmin_(0.26), xmax_(0.27), ymin_(0), ymax_(0.01),
    stepsX_(100), stepsY_(100), maxIter_(1000),
    offset_(Complex(0,0)), enhance_(1), grid_(vigra::Shape2(100,100))
    
  {}
  Mandelbrot(double xmin,
	     double xmax,
	     double ymin,
	     double ymax,
	     int stepsX,
	     int stepsY,
	     ushort maxIter,
	     Complex offset,
	     uint enhance) :
    xmin_(xmin), xmax_(xmax), ymin_(ymin), ymax_(ymax),
    stepsX_(stepsX), stepsY_(stepsY), maxIter_(maxIter),
    offset_(offset), enhance_(enhance), grid_(vigra::Shape2(stepsX, stepsY))
  {}


  void setCoord(double xmin, double xmax, double ymin, double ymax);
  void setSteps(int stepsX, int stepsY);
  void setIter(ushort maxIter);
  void setEnhance(uint enhance);
  void fillGrid();
  int calculateElement(Complex& z, Complex& c, int iterations, const Complex& offset);
  // bool writeToFile(const char *filename) const;
  void writeImage(const char *filename) const;
  const vigra::MultiArray<2, ushort>& getImage();
};


#endif /* MANDELBROT_HXX */
