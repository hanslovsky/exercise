#include <iostream>
#include "26.hpp"
#include "../27/27.hpp"

using namespace std;


int main() {
  int dMax;
  int period;
  getLongestPeriod(1000, dMax, period);
  cout << dMax << "  " << period << "  " << 1.0/dMax << "\n";
  return 0;
}
