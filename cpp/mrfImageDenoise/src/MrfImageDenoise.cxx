#include "MrfImageDenoise.hxx"

#include <boost/random.hpp>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <cmath>
#include <list>

#include <ctime>

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
  *denoisedImage_ = noisyImage_->clone();
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


double icmInfer::updatePixel(double* im, cv::Mat& changeFlags, int c, int r, int M, int N) {
  std::list<int> neighbors(4,0);
  if (r == 0) {
    if (c == 0) {
      neighbors = std::list<int>(upperLeft_, upperLeft_ + 2);
    } else if (c == N-1) {
      neighbors = std::list<int>(upperRight_, upperRight_ + 2);
    } else {
      neighbors = std::list<int>(upper_, upper_ + 3);
    }
  } else if ( r == M-1) {
    if (c == 0) {
      neighbors = std::list<int>(lowerLeft_, lowerLeft_ + 2);
    }
    if (c == N-1) {
      neighbors = std::list<int>(lowerRight_, lowerRight_ + 2);
    }
    else {
      neighbors = std::list<int>(lower_, lower_ + 3);
    }
  } else if (c ==0) {
    neighbors = std::list<int>(left_, left_ + 3);
  } else if (c == N-1) {
    neighbors = std::list<int>(right_, right_ + 3);
  } else {
    neighbors = std::list<int>(regular_, regular_ + 4);
    } 
  return udpatePixelCore(im, changeFlags, c, r, neighbors, N);
}



double icmInfer::udpatePixelCore(double* im, cv::Mat& changeFlags, int c, int r, std::list<int> neighbors, int N) {
  
  int index = r*N + c;
  int nNeighbors = neighbors.size();
  double* data = im;
  double neighborSum = 0.0;
  double* pixel = data + index;
  double oldPixelValue = *pixel;
  *pixel *= lambda_;
  for (std::list<int>::iterator it = neighbors.begin(); it != neighbors.end(); it++) {
     *pixel += *(pixel + *it);
  }
  *pixel /= (lambda_ + nNeighbors);
  data = 0;
  double n = *pixel;
  pixel = 0;
  return  n - oldPixelValue;
}
  

void icmInfer::defineNeighbors(int N) {
  regular_[0] = 1, regular_[1] = -1, regular_[2] = N, regular_[3] = -N;
  upperLeft_[0] = 1, upperLeft_[1] = N;
  lowerLeft_[0] = 1, lowerLeft_[1] = -N;
  lowerRight_[0] = -1, lowerRight_[1] = -N;
  upperRight_[0] = -1, upperRight_[1] = N;
  left_[0] = 1, left_[1] = N, left_[2] = -N;
  lower_[0] = 1, lower_[1] = -1, lower_[2] = -N;
  right_[0] = -1, right_[1] = N, right_[2] = -N;
  upper_[0] = 1, upper_[1] = -1, upper_[2] = N;
}
  
				 

void icmInfer::operator() (cv::Mat_<double>* im1, cv::Mat_<double>* im2) {
  int M = im1->rows;
  int N = im1->cols;
  defineNeighbors(N);
  int numberOfPixels = M*N;
  cv::Mat changeFlags = cv::Mat::zeros(M, N, CV_8UC1);
  double nPixels = M*N;
  int count = 0;
  double change = 0.0;
  int index = 0;
  double* d1 = (double*) im1->data;
  double* d2 = (double*) im2->data;
  unsigned char* flags = (unsigned char*) changeFlags.data;
  double denominator = 1.0 + 4.0*lambda_;
  while (count < maxIter_) {
    change = 0.0;
    for (int r = 1; r < M-1; r++) {
      index = r*N;
      for (int c = 1; c < N-1; c++) {


	/* double old = *(d2 + index);
	// rewrite to:
	// if corner -> calculateCornerValue
	// if edge -> calculateEdgeValue
	// if regular -> calculateRegularValue
	// also: include maximum penalty for smoothing
	*(d2 + index) = (*(d2 + index) + lambda_ * (*(d2 + index + 1) +
						   *(d2 + index - 1) +
						   *(d2 + index + N) +
						   *(d2 + index - N)));
	*(d2 + index) /= denominator;
	double localChange = abs(*(d2 + index) - old); */
	
	double tmp = updatePixel(d2, changeFlags, c, r, M, N);
	double localChange = abs(tmp);
	
	// end rewrite
	// change += localChange;
	if (localChange > 1)
	  *(flags + index) = 1;
	else
	  *(flags + index) = 0;
	index++;
      }
    }
    change /= (1.0*numberOfPixels);
    if (change < epsilon_)
      break;
    count++;
  }
  
  std::cout << change << "  " << epsilon_ << "\n";
  std::cout << count << "\n";
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
  
