#include "MrfImageDenoise.hxx"
#include <iostream>


using namespace std;

int main() {
  NoisyImage im("map.png");
  im.gaussianNoiseImage(100, 0);

  // binaryFunctor binFn;
  icmInfer icm(0.1, 1000, 0.00000000000000000000001);
  im.infer<icmInfer>(icm);
  // im.infer<binaryFunctor>(binFn);
  
  im.showImages();
  // lTwoSquared<int> l2;
  // cout << distance<double, lTwoSquared<int> > (5.5, 3, l2) << "\n";
  return 0;
}
