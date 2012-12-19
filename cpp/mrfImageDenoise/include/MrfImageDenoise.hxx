#ifndef __MRF_IMAGE_DENOISE_HXX__
#define __MRF_IMAGE_DENOISE_HXX__

#include <iostream>
#include <opencv2/core/core.hpp>
#include <list>



// class to hold noisy image and provide functionality to denoise image
// using mrf
// idea taken from http://www.cs.toronto.edu/~fleet/courses/2503/fall11/Handouts/mrf.pdf
// also provides function to put noise on image

class NoisyImage {
  cv::Mat_<double>* noisyImage_;
  cv::Mat_<double>* denoisedImage_;
public:
  NoisyImage() : noisyImage_(0), denoisedImage_(0) {}
  NoisyImage(const char* fn);
  ~NoisyImage();
  void readImage(const char* fn);
  void gaussianNoiseImage(double variance = 1, double mean = 0);
  void writeImage(const char* fn);
  template <typename BinaryFn>
  void infer(BinaryFn algorithm);
  void showImages();
};

// arbitrary function can be used for inference
// the user can specify the inference algorithm
// the binary function takes two pointers to cv::Mat_<double>
// as input arguments
template <typename BinaryFn>
void NoisyImage::infer(BinaryFn algorithm) {
  if (noisyImage_ == 0) {
    throw 2;
  }
  if (denoisedImage_ == 0) {
    denoisedImage_ = new cv::Mat_<double>(noisyImage_->clone());
  }
  algorithm(noisyImage_, denoisedImage_);
}


// test binary functor that just produces two constant images
class binaryFunctor {
  double x1_;
  double x2_;
public:
  binaryFunctor(double x1 = 85, double x2 = 170) : x1_(x1), x2_(x2) {
    if (x1_ > 255)
      x1_ = 85;
    if (x2_ > 255)
      x2_ = 170;
  }
  void operator() (cv::Mat_<double>* im1, cv::Mat_<double>* im2) {
    int rows = im1->rows;
    int cols = im1->cols;
    *im1 = cv::Mat::zeros(rows, cols, CV_64F) + x1_;
    *im2 = cv::Mat::zeros(rows, cols, CV_64F) + x2_;
  }
};

// binary functor implementing icm for inference
class icmInfer {
  // parameters
  double lambda_;
  unsigned maxIter_;
  double epsilon_;
  // neighbors relative to requested pixel
  int regular_[4];
  int upperLeft_[2];
  int lowerLeft_[2];
  int lowerRight_[2];
  int upperRight_[2];
  int left_[3];
  int lower_[3];
  int right_[3];
  int upper_[3];
  // update pixel based on neighborhood and pixel value
  double updatePixel(cv::Mat_<double>* im, cv::Mat& changeFlags, int r, int c);
  double udpatePixelCore(cv::Mat_<double>* im, cv::Mat& changeFlags, int c, int r, std::list<int> neighbors);
  // define neighbors as soon as dims of matrix are known
  void defineNeighbors(int N);
public:
  icmInfer(double lambda, unsigned maxIter, double epsilon) : \
    lambda_(lambda), maxIter_(maxIter), epsilon_(epsilon) {}
  void operator() (cv::Mat_<double>* im1, cv::Mat_<double>* im2);
};


double randomFromNormal(double mean = 0.0, double variance = 1.0);
void randomVectorFromNormal(int N, double* numbers,
		      double mean = 0.0, double variance = 1.0);


// use functors to allow for various metrics
template <typename T, typename BinaryFn>
double distance(T p1, T p2, BinaryFn metric) { // = lTwoSquared<double>()) {
  return metric(p1, p2);
}


// l2Squared
template <typename T>
class lTwoSquared {
public:
  lTwoSquared() {}
  double operator() (T, T);
};

template <typename T>
double lTwoSquared<T>::operator() (T p1, T p2) {
  return static_cast<double> ((p1-p2)*(p1-p2));
}


#endif /* __MRF_IMAGE_DENOISE_HXX__ */
