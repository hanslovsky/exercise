#include <img2ascii.hxx>
#include <opencv2/imgproc/imgproc.hpp>
#include <vector>
#include <iostream>

void preProcess(const cv::Mat_<uchar>& image, cv::Mat_<uchar>& edges) {
  Canny(image, edges, 50, 200, 3);
}


double getParameters(const cv::Mat_<uchar>& image, double parameters[2]) {

  // vector to store coordinates(1, x, y)
  // neccessary for calculation of least squares
  std::vector<std::vector<int> > coordinates;
  for (int i = 0; i < 3; i++) {
    std::vector<int> a;
    coordinates.push_back(a);
  }
  for (int y = 0; y < image.rows; y++) {
    int stride = image.step*y;
    for (int x = 0; x < image.cols; x++) {
      int value = (int)(image.data + stride)[x];
      if (value > 0) {
	coordinates.at(0).push_back(1);
	coordinates.at(1).push_back(x);
	coordinates.at(2).push_back(y);
      }
    }
  }

  
  uint samples = coordinates.at(0).size();
  // if only few points are part of edge: return
  // high SSQ
  if (samples < 0.3*image.rows*image.cols) {
    return 9999999999.0;
  }
  // convert vectors to cv::Mat
  cv::Mat_<double> X(2, samples);
  cv::Mat_<double> Y(1, samples);
  for (unsigned int i = 0; i < samples; i++) {
    X.at<double>(0,i) = coordinates.at(0).at(i);
    X.at<double>(1,i) = coordinates.at(1).at(i);
    Y.at<double>(0,i) = coordinates.at(2).at(i);
  }

  // calculate least square parameters (w) and
  // sum of squared errors (SSQ)
  cv::Mat w = (X*X.t()).inv()*X*Y.t();
  cv::Mat_<double> SSQ = (Y - w.t()*X)*(Y - w.t()*X).t();
  parameters[0] = w.at<double>(0,0);
  parameters[1] = w.at<double>(0,1);
  

  return SSQ.at<double>(0,0)/samples;
}


std::string setCharacters(const cv::Mat_<uchar>& image,
			  int width,
			  int height,
			  double SSQ_thresh
			  ) {
  int rows = image.rows;
  int cols = image.cols;
  cv::Mat_<uchar> edges;
  preProcess(image, edges);

  std::string asciiString = "";
  double param[2];
  char symbols[NUMBER_OF_SYMBOLS] = SYMBOLS;
  
  for (int y = 0; y < rows - height; y += height) {
    for (int x = 0; x < cols - width; x += width) {
      cv::Rect box(x, y, width, height);
      double SSQ = getParameters(edges(box), param);
      double intercept = param[0];
      double m = param[1];

      if (SSQ < SSQ_thresh) {
	if (m >= 0.6 && m <= 1.7) {
	  asciiString += "\\";
	} else if (m > 1.7 or m < -1.7) {
	  asciiString += "|";
	} else if (m <= -0.6 && m >= -1.7) {
	  asciiString += "/";
	} else {
	  if (intercept > 0.7*height) {
	    asciiString += "_";
	  } else {
	    asciiString += "-";
	  }
	}
      } else {
	double mean = cv::mean(image(box))(0);
	int index = (int) ( (1 - mean/255.0) * NUMBER_OF_SYMBOLS);
	asciiString += symbols[index];
      }
    }
    asciiString += "\n";
  }
  return asciiString;
}
