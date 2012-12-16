#include "MrfImageDenoise.hxx"

#include <boost/random.hpp>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

NoisyImage::NoisyImage(const char* fn) : noisyImage_(0), denoisedImage_(0) {
  readImage(fn);
}


NoisyImage::~NoisyImage() {
  delete noisyImage_;
  delete denoisedImage_;
}


void NoisyImage::readImage(const char* fn) {
  delete noisyImage_;
  noisyImage_ = new cv::Mat_<double>;
  *noisyImage_ = cv::imread(fn, CV_LOAD_IMAGE_GRAYSCALE);
}


void NoisyImage::gaussianNoiseImage(double variance, double mean) {
  if (noisyImage_ == 0) {
    throw 1;
  }
  int M = noisyImage_->rows;
  int N = noisyImage_->cols;
  double* it = (double*) noisyImage_->data;
  for (int m = 0; m < M; m++) {
    for (int n = 0; n < N; n++) {
      *it += randomFromNormal(mean, variance);
      it++;
    }
  }
  cv::Mat_<double> tmp(M, N);
  double min, max;
  cv::minMaxLoc(*noisyImage_, &min, &max);
  double range = max - min;
  *noisyImage_ = (*noisyImage_ - min)*(255.0/range);
  cv::imwrite("bla.png", *noisyImage_);
}


double randomFromNormal(double mean, double variance) {
  // create random number generator
  static boost::mt19937 rng(static_cast<unsigned> (time(0)));
  boost::normal_distribution<double> gaussian(mean, variance);
  boost::variate_generator<boost::mt19937&, \
			   boost::normal_distribution<double> > generator(rng, gaussian);
  return generator();
}


void randomVectorFromNormal(int N, double* numbers,
			    double mean, double variance) {
  double* it = numbers;
  for (int i = 0; i < N; i++, it++) {
    *it = randomFromNormal(mean, variance);
  }
}
  
