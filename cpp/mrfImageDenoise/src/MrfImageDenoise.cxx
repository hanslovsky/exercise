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
  // temporary: write original image in larger image for
  // the purpose of showing it later
  cv::Mat large = cv::Mat::zeros(M+4, 2*N+6, CV_8UC1);
  cv::Mat tmp = large(cv::Rect(2,2, N, M));
  noisyImage_->convertTo(tmp, CV_8UC1);
  /* temporary */
  double* it = (double*) noisyImage_->data;
  for (int m = 0; m < M; m++) {
    for (int n = 0; n < N; n++) {
      *it += randomFromNormal(mean, variance);
      it++;
    }
  }
  double min, max;
  cv::minMaxLoc(*noisyImage_, &min, &max);
  double range = max - min;
  *noisyImage_ = (*noisyImage_ - min)*(255.0/range);
  // temporary: show and write noisy image
  cv::imwrite("bla.png", *noisyImage_);
  cv::namedWindow("noisy image", CV_WINDOW_AUTOSIZE);
  cv::Mat_<unsigned char> a = cv::imread("bla.png", CV_LOAD_IMAGE_GRAYSCALE);
  tmp = large(cv::Rect(N+4, 2, N, M));
  a.copyTo(tmp);
  cv::imshow("noisy image", large);
  cv::waitKey(0);
  /* temporary */
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
  
