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
  delete denoisedImage_;
  noisyImage_ = new cv::Mat_<double>;
  *noisyImage_ = cv::imread(fn, CV_LOAD_IMAGE_GRAYSCALE);
  denoisedImage_ = new cv::Mat_<double>(noisyImage_->clone());
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
  double min, max;
  cv::minMaxLoc(*noisyImage_, &min, &max);
  double range = max - min;
  *noisyImage_ = (*noisyImage_ - min)*(255.0/range);
  // temporary: write noisy image
  cv::imwrite("bla.png", *noisyImage_);
  /* temporary */
}


void NoisyImage::showImages() {
  if (noisyImage_ == 0 or denoisedImage_ == 0) {
    throw 1;
  }
  int M = noisyImage_->rows;
  int N = noisyImage_->cols;
  
  // large image to hold both noisy and denoised image
  cv::Mat large = cv::Mat::zeros(M+4, 2*N+6, CV_8UC1);

  // noisyImage_ as subimage of large
  cv::Mat tmp = large(cv::Rect(2,2, N, M));
  noisyImage_->convertTo(tmp, CV_8UC1);
  cv::namedWindow("noisy image", CV_WINDOW_AUTOSIZE);

  // denoisedImage_ as subimage of large
  tmp = large(cv::Rect(N+4, 2, N, M));
  denoisedImage_->convertTo(tmp, CV_8UC1);
  
  cv::imshow("noisy image", large);
  cv::waitKey(0);
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
  
