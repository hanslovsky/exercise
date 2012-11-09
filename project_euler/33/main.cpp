#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// calculate greatest common divisor
int gcd(int num, int den) {
  if (num < 0)
    num = -num;
  if (den < 0)
    den = -den;
  if (num == 0 || den == 0)
    return 0;
  if (num % den == 0)
    return den;
  else if (den % num == 0)
    return num;
  
  else {
    int minVal = min(den, num);
    int divisor = 1;
    for (int i = 1; i <= minVal/2; i++) {
      if ((den % i == 0) & (num % i == 0))
	divisor = i;
    }
    return divisor;
  }
}

// find numbers with unorthodox cancelling method
// possible numbers:
// n/d = (10n+i)/(10d+i) -> does not work
// n/d = (10i+d)/(10i+n) -> does not work
// n/d = (10i+n)/(10d+i) -> does not work
// n/d = (10n+i)/(10i+d) -> does work
// s.t.
// i>d>n>0
// 10i+d < 100

void getUnorthodox(vector<int>& num, vector<int>& den) {
  for (int i = 3; i < 10; i++) {
    for (int d = 2; d < i; d++) {
      for (int n = 1; n < d; n++) {
	int numerator = 10*n + i;
	int denominator = 10*i + d;
	if (d*numerator == n*denominator) {
	  int divisor = gcd(numerator, denominator);
	  num.push_back(numerator/divisor);
	  den.push_back(denominator/divisor);
	}
      }
    }
  }
}

// multiply several ratios given by vector of numerators and
// vector of denominators
void multiplyRatio(const vector<int>& num, const vector<int>& den,
		  int& numResult, int& denResult) {
  numResult = 1;
  denResult = 1;
  vector<int>::const_iterator it1, it2;
  it1 = num.begin();
  it2 = den.begin();
  while(it1 != num.end() && it2 != den.end()) {
    numResult *= *it1;
    denResult *= *it2;
    it1++, it2++;
  }
}

int main() {
  vector<int> num;
  vector<int> den;
  int numResult, denResult;

  getUnorthodox(num, den);
  multiplyRatio(num, den, numResult, denResult);
  int divisor = gcd(numResult, denResult);


  vector<int>::iterator it1, it2;
  it1 = num.begin();
  it2 = den.begin();
  for (; it1 != num.end() && it2 != den.end(); it1++, it2++) {
    cout << *it1 << "/" << *it2 << "\n";
  }
  
  cout << numResult/divisor << "/" << denResult/divisor << "\n";
  cout << divisor << "\n";
}
