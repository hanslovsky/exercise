#include <iostream>
#include <fstream>
#include "include/PNGImage.hxx"
#include <cmath>

using namespace std;

int main() {
  ifstream s;
  ifstream bla;
  s.open("1a_hot.png");
  bla.open("bla");
  int length = 0;
  s.seekg(0, ios::end);
  length = s.tellg();
  s.seekg(0, ios::beg);
  double size = length*1.0/1024;
  cout << length << " " << size << endl;
  cout << isPNG(s) << endl;
  cout << isPNG(bla) << endl;
  bla.close();
  s.close();
  cout << "reopen" << endl;
  s.open("test.png");
  PNGImage img;
  bool r = readPNG(bla, img);
  cout << r << endl;
  r = readPNG(s, img);
  s.close();
  cout << r << endl;
  cout << "width=" << img.getSizeX() <<", height=" << img.getSizeY() << ", color type=" << img.getColorType() << endl;
  //img.printPixels();
  int *pa;
  cout << pa << endl;
  return 0;
}
