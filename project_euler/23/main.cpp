#include <iostream>
#include <numeric>
#include <vector>
#include <set>
#include <math.h>

using namespace std;


void getProperDivisors(int n, vector<int>& divisors) {
  int maxN = (int)sqrt(n);
  if (maxN*maxN == n) {
    divisors.push_back(maxN);
    maxN--;
  }
  divisors.reserve(2*n);
  divisors.push_back(1);
  for (int i = 2; i <= maxN; i++) {
    if ((n % i) == 0) {
      divisors.push_back(i);
      divisors.push_back((int)(n/i));
    }
  }
}


bool checkAbundant(int n) {
  vector<int> div;
  getProperDivisors(n, div);
  if (accumulate(div.begin(), div.end(), 0) > n)
    return true;
  else
    return false;
}

void getAbundants(int n, vector<int>& abundants) {
  for (int i = 12; i < n; i++) {
    if (checkAbundant(i)) {
      abundants.push_back(i);
    }
  }
}

void listPossibleAsAbundants(int n, set<int>& abundantSums) {
  vector<int> ab;
  getAbundants(n, ab);
  for (int i = 0; i < ab.size(); i++) {
    int abSum = 0;
    for (int j = i; j < ab.size() && abSum < n; j++) {
      abSum = ab.at(i) + ab.at(j);
      if (abSum < n) {
	abundantSums.insert(abSum);
      }
    }
  }
}

int sumPossibleAsAbundants(int n) {
  int sum = 0;
  set<int> abSums;
  listPossibleAsAbundants(n, abSums);
  set<int>::iterator itBegin = abSums.begin();
  set<int>::iterator it = itBegin;
  for (int i = 0; i < n; i++) {
    bool notInList = true;
    for (; it != abSums.end() && *it <= i; it++) {
      if (i == *it) {
	notInList = false;
      }
    }
    if (notInList)
      sum += i;
  }
  return sum;
}
	

int main() {
  cout << sumPossibleAsAbundants(28123) << "\n";
  /*set<int> abSums;
  listPossibleAsAbundants(28123, abSums);
  cout << *(abSums.begin()) << endl;*/
  return 0;
}
