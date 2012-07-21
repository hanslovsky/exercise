#include "../include/mandelbrot.hxx"
#include "../include/complex.hxx"
#include <iostream>
#include <fstream>

Mandelbrot::~Mandelbrot() {
  if (!grid_)
    delete grid_;
}

void Mandelbrot::setCoord(double xmin, double xmax, double ymin, double ymax) {
  xmin_ = xmin;
  xmax_ = xmax;
  ymin_ = ymin;
  ymax_ = ymax;
}

void Mandelbrot::setSteps(int stepsX, int stepsY) {
  stepsX_ = stepsX;
  stepsY_ = stepsY;
}

void Mandelbrot::setIter(int maxIter) {
  maxIter_ = maxIter;
}

void Mandelbrot::fillGrid() {
  if (!grid_) {
    delete grid_;
    grid_ = 0;
  }
  grid_ = new std::vector<std::vector<double > >(stepsY_, std::vector<double> (stepsX_));
  double stepSizeX = (xmax_ - xmin_)/stepsX_;
  double stepSizeY = (ymax_ - ymin_)/stepsY_;
  for (int y = 0; y < stepsY_; y++) {
    double im = ymin_ + y*stepSizeY;
    for (int x = 0; x < stepsX_; x++) {
      double re = xmin_ + x*stepSizeX;
      Complex c(re, im);
      Complex z(0, 0);
      int iterations = maxIter_;
      while (iterations > 0) {
	if (z.sqAbs() >= 4) {
	  break;
	}
	z = z*z;
	z = z + c;
	iterations--;
      }
      double gridValue = 1.0*iterations/maxIter_;
      grid_->at(y).at(x) = gridValue;
    }
  }
}

bool Mandelbrot::writeToFile(const char *filename) const {
  if (!grid_) {
    return 0;
  }
  std::ofstream f(filename, std::ios::trunc);
  if (f.is_open()) {
    for (int y = 0; y < stepsY_; y++) {
      for (int x = 0; x < stepsX_; x++) {
	f << grid_->at(y).at(x) << " ";
      }
      f << "\n";
    }
    f.close();
  }
  else {
    return 0;
  }
  return 1;
}
