o#include "slic.hxx"
#include <iostream>
#include <algorithm>

// #include <vigra/stdimage.hxx>
#include <vigra/impex.hxx>

using namespace std;
using namespace vigra;

int main() {
  int k = 2;
  int nDim = 2;
  double data[20] = {5,3,4,3,4.5,4,0,0,2,1,
		     -2,0,-1,1,-1,-1,-5,2,0.5,-1};
  double clusters[k];
  int labels[10] = {0};
  L2SquaredArray<double> l2;
  KMeans<double, L2SquaredArray<double> > km(l2, k);
  cout << km.infer(data, 10, nDim, labels, clusters) << "\n";
  for (int i = 0; i < 10; i++) {
    cout << labels[i] << "\n";
  }
  cout << "\n";
  for (int i = 0; i < k*nDim; i+=nDim) {
    cout << "(";
    for (int r = 0; r < nDim; r++) {
      cout << clusters[nDim*i+r] << ",";
    }
    cout << "\b)\n";
    // try SLIC!
  }
  ImageImportInfo info("lena.jpg");
  BRGBImage img(info.width(), info.height());
  vigra::importImage(info, destImage(img));
  Slic<2> slic(img, 16, 16, 20.0, 0.5);
  // slic.infer();
  return 0;
}
