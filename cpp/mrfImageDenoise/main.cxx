#include "MrfImageDenoise.hxx"
#include <iostream>


using namespace std;

int main() {
  NoisyImage im("map.png");
  im.gaussianNoiseImage(100, 0);
  lTwoSquared<int> l2;
  cout << distance<double, lTwoSquared<int> > (5.5, 3, l2) << "\n";
  return 0;
}
