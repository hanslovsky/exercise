#include <iostream>
#include "27.hpp"

using namespace std;

int main() {
  // aCondition conditions on the relation of a, b and d 
  // for the feasible region:
  //
  // a > -(b/n+n)
  //
  //
  // nCondition conditions on the relation of a and n for
  // the feasible region:
  // WRONG CONDITION!!
  // n > -a/2
  //
  //
  // primeCondition is true as long n^2 + an + b is prime


  int argmaxA = 0, argmaxB = 0;
  int maxLengthPrimes = 0;
  int number;
  for (int b = 2; b < 1000; b++) {
    if (!isPrime(b))
      continue;
    for (int a = -999; a < 1000; a++) {
      int length = 0;
      bool aCondition = true;
      bool primeCondition = true;
      bool containCondition = true;
      for (int n = 0; containCondition && primeCondition && aCondition; n++) {
	number = n*n + a*n + b;
	if (number < 0)
	  aCondition = false;
	else if (!isPrime(number))
	  primeCondition = false;
	else
	  length ++;
      }
      if (length > maxLengthPrimes) {
	maxLengthPrimes = length;
	argmaxA = a;
	argmaxB = b;
      }
    }
  }

  cout << argmaxA << "  " << argmaxB << "\n";
  cout << maxLengthPrimes << "  " << argmaxA*argmaxB << "\n";
  return 0;
}
