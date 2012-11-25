#include "40.hpp"
#include <iostream>
#include <string>
#include <math.h>

using namespace std;

int main() {
  cout << getDecimalFraction(14) << "\n";
  cout << getDigit(getDecimalFraction(14), 9) << "\n";
  int max = 6;
  string num = getDecimalFraction(pow(10,max));
  for (int i = 0; i <= max; i++) {
    cout << getDigit(num, pow(10, i)) << "  ";
  }
  cout << "\n";
  return 0;
}
