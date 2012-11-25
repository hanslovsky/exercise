#ifndef EULER_40_HPP
#define EULER_40_HPP

#include <iostream>
#include <sstream>
#include <string>



// calculate decimal fraction by concatenating positive integers
// maxDigit is the maximum digit that needs to be contained
// as soon as the length of the fraction is greater or equal
// to maxDigit the fraction is returned
std::string getDecimalFraction(int maxDigit) {
  std::string fraction = "";
  int i = 1;
  while(fraction.size() < maxDigit) {
    std::stringstream number;
    number << i;
    fraction += number.str();
    i++;
  }
  return fraction;
}

int getDigit(std::string fraction, int n) {
  if (n > fraction.size())
    throw std::exception();
  if (n < 1)
    throw std::exception();
  n--;
  int digit = (int) fraction[n] - '0';
  return digit;
}


#endif
