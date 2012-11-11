#ifndef EULER_27_HPP
#define EULER_27_HPP

#include <iostream>
#include <math.h>
#include <vector>

bool isPrime(int n) {
  if (n < 2)
    return false;
  int upperLimit = (int)sqrt(n);
  for (int i = 2; i <= upperLimit; i++) {
    if (i*(n/i) == n)
      return false;
  }
  return true;
}

template <class T>
bool isContained(std::vector<T> vc, T el) {
  for (typename std::vector<T>::iterator it = vc.begin();
       it != vc.end(); it++) {
    if (*it == el)
      return true;
  }
  return false;
}

#endif
