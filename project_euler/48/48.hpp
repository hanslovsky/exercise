#ifndef EULER_48_HPP
#define EULER_48_HPP

#include <iostream>
#include <math.h>
#include <limits>

// Power Series := 1^1 + 2^2 + ... + nMax^nMax
long findLastDigitsOfPowerSeries(int nMax, long nLastDigits = 10) {
  long modulo = pow(10, nLastDigits);
  long result = 0;
  long longMax = std::numeric_limits<long>::max();
  long modLimit = longMax/nMax;
  for (int i = 1; i <= nMax; i++) {
    long tmp = i;
    for (int j = 1; j < i; j++) {
      tmp *= i;
      if (tmp >= modLimit)
	tmp %= modulo;
    }

  result += tmp;
  result %= modulo;
  }
  return result;
}

#endif
