// stl
#include <iostream>
#include <fstream>
#include <stdexcept>

// vigra
#include <vigra/impex.hxx>
#include <vigra/multi_array.hxx>
#include <vigra/multi_iterator.hxx>

// own
#include "mandelbrot.hxx"
#include "complex.hxx"


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

void Mandelbrot::setIter(ushort maxIter) {
  maxIter_ = maxIter;
}

void Mandelbrot::setEnhance(uint enhance) {
  enhance_ = enhance;
}

void Mandelbrot::fillGrid() {
  if (enhance_ < 1) {
    throw std::runtime_error("Enhance set to value smaller than 1!");
  }
  vigra::Shape2 shape(stepsX_, stepsY_);
  if (grid_.shape()[0] != shape[0] || grid_.shape()[1] != shape[1]) {
    grid_.reshape(shape);
  }
  
  // vigra::BImage::Iterator ity = grid_->upperLeft();
  // vigra::BImage::Iterator end = grid_->lowerRight();
  Iterator2D it_y = grid_.traverser_begin();
  double stepSizeX = (xmax_ - xmin_)/stepsX_;
  double stepSizeY = (ymax_ - ymin_)/stepsY_;
  
  for (int y = 0; it_y != grid_.traverser_end(); ++it_y, ++y) {
    double im = ymin_ + y*stepSizeY;
    Complex c(0, im);
    Iterator1D it_x = grid_.bindAt(1, y).traverser_begin();
    
    for (int x = 0; it_x != grid_.bindAt(1, y).traverser_end(); ++it_x) {
      double re = xmin_ + x*stepSizeX;
      c.setR(re);
      Complex z(re, im);
      int iterations = calculateElement(z, c, maxIter_ - 1, offset_);
      double gridValue = (1.0*iterations)/maxIter_;
      gridValue = 255*pow(gridValue, enhance_);
      *it_x = static_cast<ushort>(gridValue);
    }
  }
}
          




/* Complex offset = offset_;
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
} */


int Mandelbrot::calculateElement(Complex& z, Complex& c, int iterations, const Complex& offset) {
  --iterations;
  while (iterations > 0) {
    if (z.sqAbs() >= 4) {
      break;
    }
    z = z*z;
    z = z + c + offset;
    --iterations;
  }
    return iterations;
}
       


/* bool Mandelbrot::writeToFile(const char *filename) const {
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
  } */

void Mandelbrot::writeImage(const char *filename) const {
  exportImage(srcImageRange(grid_), vigra::ImageExportInfo(filename));
}

const vigra::MultiArray<2, ushort>& Mandelbrot::getImage() {
  return grid_;
}
