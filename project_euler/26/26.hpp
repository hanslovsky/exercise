#ifndef EULER_26_HPP
#define EULER_26_HPP

#include <iostream>
#include <math.h>
#include <vector>
#include "../27/27.hpp"

int getNoDigits(int n) {
  if (n < 0)
    n = -n;
  if (n < 10)
    return 1;
  if (n < 100)
    return 2;
  if (n < 1000)
    return 3;
  if (n < 10000)
    return 4;
  if (n < 100000)
    return 5;
  if (n < 1000000)
    return 6;
  if (n < 10000000)
    return 7;
  if (n < 100000000)
    return 8;
  if (n < 1000000000)
    return 9;
  else
    return 10;
}

int getNoDigitsUInt(uint n) {
  if (n < 10)
    return 1;
  if (n < 100)
    return 2;
  if (n < 1000)
    return 3;
  if (n < 10000)
    return 4;
  if (n < 100000)
    return 5;
  if (n < 1000000)
    return 6;
  if (n < 10000000)
    return 7;
  if (n < 100000000)
    return 8;
  if (n < 1000000000)
    return 9;
  else
    return 10;
}

void division(int dividend, int divisor,
	      double& result, int& periodLength) {
  int sign = 1;
  if ((dividend > 0 && divisor < 0)) {
    divisor = -divisor;
    sign = -1;
  }
  if ((dividend < 0 && divisor > 0)) {
    dividend = -dividend;
    sign = -1;
  }
  if ((dividend < 0 && divisor < 0)) {
    dividend = -dividend;
    divisor = -divisor;
  }
  int noDigits = getNoDigits(dividend);
  int digit = noDigits - 1;
  int rest = 0;
  int valueAtDigit = 0;
  std::vector<int> rests;
  periodLength = 0;
  result = 0;
  while(true) {
    if (digit < 0)
      valueAtDigit = 10*rest;
    else 
      valueAtDigit = (dividend/pow(10, digit) + rest*10);
    int div = valueAtDigit/divisor;
    rests.push_back(rest);
    result += div*pow(10, digit);
    rest = valueAtDigit - div*divisor;
    if (isContained<int>(rests, rest))
      break;
    digit--;
    periodLength++;
  }
  result = sign*result;
}

void getLongestPeriod(int n, int& dMax, int& period) {
  dMax = 0;
  period = 0;
  int pL = 0;
  double result;
  for (int d = n; d > 2; d--) {
    if (!isPrime(d))
      continue;
    if (d < dMax)
      break;
    division(1, d, result, pL);
    if (pL > period) {
      period = pL;
      dMax = d;
    }
  }
}

#endif
