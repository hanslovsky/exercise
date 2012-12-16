#ifndef __MRF_IMAGE_DENOISE_HXX__
#define __MRF_IMAGE_DENOISE_HXX__

#include <iostream>
#include <opencv2/core/core.hpp>



// class to hold noisy image and provide functionality to denoise image
// using mrf
// idea taken from http://www.cs.toronto.edu/~fleet/courses/2503/fall11/Handouts/mrf.pdf
// also provides function to put noise on image

class NoisyImage {
  cv::Mat_<double>* noisyImage_;
  cv::Mat_<double>* denoisedImage_;
  void forumlate(double lambda);
public:
  NoisyImage() : noisyImage_(0), denoisedImage_(0) {}
  NoisyImage(const char* fn);
  ~NoisyImage();
  void readImage(const char* fn);
  void gaussianNoiseImage(double variance = 1, double mean = 0);
  void denoiseImage(double lambda = 1.0, int maxIter = 1000);
  void writeImage(const char* fn);
};

double randomFromNormal(double mean = 0.0, double variance = 1.0);
void randomVectorFromNormal(int N, double* numbers,
		      double mean = 0.0, double variance = 1.0);


#endif /* __MRF_IMAGE_DENOISE_HXX__ */
