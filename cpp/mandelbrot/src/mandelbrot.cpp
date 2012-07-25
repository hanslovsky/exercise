#include <mandelbrot.hxx>
#include <complex.hxx>
#include <iostream>
#include <fstream>
#include <vigra/impex.hxx>


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

void Mandelbrot::setEnhance(uint enhance) {
  enhance_ = enhance;
}

void Mandelbrot::fillGrid() {
  if (enhance_ < 1) {
    throw 1;
  }
  if (!grid_) {
    delete grid_;
    grid_ = 0;
  }
  grid_ = new vigra::BImage(stepsX_, stepsY_);
  vigra::BImage::Iterator ity = grid_->upperLeft();
  vigra::BImage::Iterator end = grid_->lowerRight();
  double stepSizeX = (xmax_ - xmin_)/stepsX_;
  double stepSizeY = (ymax_ - ymin_)/stepsY_;
  Complex offset = offset_;
  for (int y = 0; ity.y != end.y; ++y, ++ity.y) {
    double im = ymin_ + y*stepSizeY;
    Complex c(0, im);
    vigra::BImage::Iterator itx = ity;
    for (int x = 0; itx.x !=end.x; ++x, ++itx.x) {
      double re = xmin_ + x*stepSizeX;
      c.setR(re);
      Complex z(re, im);
      int iterations = maxIter_ - 1;
      while (iterations > 0) {
	if (z.sqAbs() >= 4) {
	  break;
	}
	z = z*z;
	z = z + c + offset;
	iterations--;
      }
      double gridValue = (1.0*iterations)/maxIter_;
      gridValue = 255*pow(gridValue, enhance_);
      *itx = (uint)gridValue;
    }
  }
}

bool Mandelbrot::writeToFile(const char *filename) const {
  if (!grid_) {
    return 0;
  }
  std::ofstream f(filename, std::ios::trunc);
  if (f.is_open()) {
    vigra::BImage::Iterator ity = grid_->upperLeft();
    vigra::BImage::Iterator end = grid_->lowerRight();
    for (; ity.y != end.y; ++ity.y) {
      vigra::BImage::Iterator itx = ity;
      for (; itx.x != end.x - 1; ++itx.x) {
	f << (uint)*itx << " ";
      }
      ++itx.x;
      f << (uint)*itx << "\n";
    }
    f.close();
  }
  else {
    return 0;
  }
  return 1;
}

bool Mandelbrot::writeImage(const char *filename) const {
  if (!grid_)
    return 0;
  exportImage(srcImageRange(*grid_), vigra::ImageExportInfo(filename));
  return 1;
}
