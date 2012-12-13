#include "49.hpp"
#include <iostream>

using namespace std;

int main() {
  int iBasis = 0;
  int jStep = 0;
  bool notFound = true;
  for (int i = 1000; i < 10000 && notFound; i++) {
    int stepSizelimit = (10000 - i)/2 + 1;
    for (int j = 1; j < stepSizeLimit && notFound; j++) {
      if (isPermutation(i, i+j) && isPermutation(i, i+2*j)) {
	iBasis = i;
	jStep = j;
	notFound = false;
      }
    }
    cout << iBasis << "  " << jStep << "\n";
  }
  return 0;
}
