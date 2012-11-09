#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int factorial(int n) {
  if (n == 0) {
    return 1;
  }
  int result = n;
  while(n > 1) {
    result *= --n;
  }
  return result;
}

int main() {

  // the first 2*362880 lexicographic permutations
  // have 0 and 1 up front. Therefore to solve this problem
  // it does make sense to start with the first lexicographic
  // permutation starting with 2, i.e. 2013456789, and find the
  // 274240th permutation of 03456789 This can be continued with the
  // other indices until the 1000000th permutation

  int perm[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  vector<int> permutations(perm, perm+10);

  int indices[10];
  int maxPerm = 1000000;
  for (int i = 9; i >= 0; i--) {
    int a = 0;
    int factorial_i = factorial(i);
    while (factorial_i*a < maxPerm) {
      a++;
    }
    a -= 1;
    maxPerm -= factorial_i*a;
    cout << maxPerm << "\n";
    indices[9-i] = a;
  }
  for (int i = 0; i < 10; i++) {
    cout << indices[i] << " ";
  }
  cout << "\n";

  vector<int>::iterator it = permutations.begin();
  for (int i = 0; i< 10; i++) {
    int index = indices[i];
    cout << *(it + index) << "";
    permutations.erase(it + index);
  }
  cout << "\n";
  return 0;
}
