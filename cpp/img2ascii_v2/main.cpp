#include <img2ascii.hxx>
#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <fstream>

using namespace std;

int main(int argc, char** argv) {


  cv::Mat dummy = cv::imread("dummy_crcl.png", 0);
  cv::Mat_<uchar> ddst;

  

  preProcess(dummy, ddst);

  double param[2];
  double SSQ = getParameters(ddst, param);
  
  cout << "w = \n" << "[ " << param[0] << " ; " << param[1] << " ]\n";
  cout << "SSQ/pixel = " << SSQ << "\n";

  //  cv::Mat image = cv::imread("circle.gif", 0);
  cv::Mat image = cv::imread("bla.jpg", 0);
  string asciiString = setCharacters(image,
				     PATCHWIDTH,
				     PATCHHEIGHT,
				     1);

  ofstream f("edges.txt");
  f << asciiString;
  f.close();
  
  return 0;
} 
