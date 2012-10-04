#ifndef IMG2ASCII_HXX
#define IMG2ASCII_HXX

#include <opencv2/core/core.hpp>
#include <string>

#ifndef SYMBOLS
#define SYMBOLS {' ', '.', ',', ':', ';', '+', '*', '&', '#', '%', '@'}
#define NUMBER_OF_SYMBOLS 11
#endif
#define PATCHWIDTH 3
#define PATCHHEIGHT 6


void preProcess(const cv::Mat_<uchar>& image, cv::Mat_<uchar>& edges);

double getParameters(const cv::Mat_<uchar>& image, double parameters[2]);

std::string setCharacters(const cv::Mat_<uchar>& image,
			  int width = PATCHWIDTH,
			  int height = PATCHHEIGHT,
			  double SSQ_thresh = 50
			  );


#endif
