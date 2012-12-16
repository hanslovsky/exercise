#include "MrfImageDenoise.hxx"
#include <iostream>


using namespace std;

int main() {
  NoisyImage im("map.png");
  im.gaussianNoiseImage(100, 0);
  return 0;
}
