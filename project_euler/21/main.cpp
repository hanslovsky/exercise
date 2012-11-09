#include <iostream>
#include <vector>
#include <math.h>
#include <numeric>

using namespace std;

void getProperDivisors(int n, vector<int>& divisors) {
  int maxN = (int)sqrt(n);
  divisors.reserve(2*n);
  divisors.push_back(1);
  for (int i = 2; i <= maxN; i++) {
    if ((n % i) == 0) {      
      divisors.push_back(i);
      divisors.push_back((int)(n/i));
    }
  }
}

int getSumAmicable(int n) {
  vector<int> div;
  getProperDivisors(n, div);
  int sumProperDivisors = accumulate(div.begin(), div.end(), 0);
  if (sumProperDivisors <= n)
    return 0;
  /* else if (sumProperDivisors == n)
    return n+n; */
  else {
    vector<int> newDiv;
    getProperDivisors(sumProperDivisors, newDiv);
    int newSumProperDivisors = accumulate(newDiv.begin(), newDiv.end(), 0);
    if (newSumProperDivisors == n) {
      return n + sumProperDivisors;
    }
    else
      return 0;
  }
  return 0;
}

int getSumAmicables(int n) {
  int sum = 0;
  for (int i = 0; i < n; i++) {
    int tmp = getSumAmicable(i);
    sum += tmp;
  }
  return sum;
}


int main() {
  cout << getSumAmicables(10000) << "\n";
}
