#include "40.hpp"
#include <iostream>
#include <string>
#include <math.h>

using namespace std;

int main() {
  int max = 6;
  string num = getDecimalFraction(pow(10,max));
  int product = 1;
  for (int i = 0; i <= max; i++) {
    int digit = getDigit(num, pow(10, i));
    cout << digit  << "  ";
    product *= digit;
  }
  cout << "\n" << product << endl;
  return 0;
}
