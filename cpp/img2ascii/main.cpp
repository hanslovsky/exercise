#include <img2ascii.hxx>
#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>


using namespace std;

int main(int argc, char** argv) {
  img2ascii a("bla.jpg");
  a.writeToFile("out.txt");
  vigra::BImage img = a.getImage();



  
  /* cv::Mat src = cv::imread("bla.jpg");
  cv::Mat dst, cdst;
  Canny(src, dst, 50, 200, 3);
  cvtColor(dst, cdst, CV_GRAY2BGR);
  std::vector<cv::Vec4i> lines;
  cv::HoughLinesP(dst, lines, 1, CV_PI/180, 20, 20, 7);
  for (size_t i = 0; i < lines.size(); i++) {
    cv::Vec4i l = lines[i];
    cv::line(cdst, cv::Point(l[0], l[1]), cv::Point(l[2], l[3]),
	     cv::Scalar(0,0,255), 1.5, CV_AA);
  }
  cv::imshow("source", src);
  cv::imshow("detected lines", cdst);
  cv::waitKey(); */

  cv::Mat dummy = cv::imread("dummy_crcl.png", 0);
  cv::Mat ddst;

  

  Canny(dummy, ddst, 50, 200, 3);
  std::vector<std::vector<int> > coordinates;
  for (int i = 0; i < 3; i++) {
    std::vector<int> a;
    coordinates.push_back(a);
  }
  for (int y = 0; y < ddst.rows; y++) {
    int stride = ddst.step*y;
    for (int x = 0; x < ddst.cols; x++) {
      int value = (int)(ddst.data + stride)[x];
      if (value > 0) {
	coordinates.at(0).push_back(1);
	coordinates.at(1).push_back(x);
	coordinates.at(2).push_back(y);
      }
    }
  }

  cv::Mat_<double> X(2, coordinates.at(0).size());
  cv::Mat_<double> Y(1, coordinates.at(2).size());
  for (unsigned int i = 0; i < coordinates.at(0).size(); i++) {
    X.at<double>(0, i) = coordinates.at(0).at(i);
    X.at<double>(1, i) = coordinates.at(1).at(i);
    Y.at<double>(0, i) = coordinates.at(2).at(i);
  }

  cv::Mat w = (X*X.t()).inv()*X*Y.t();
  cv::Mat_<double> SSQ = (Y - w.t()*X)*(Y - w.t()*X).t();
  cout << "w = \n" << w << "\n";
  cout << "SSQ/pixel = " << SSQ.at<double>(0,0)/X.cols << "\n";
  return 0;
} 
