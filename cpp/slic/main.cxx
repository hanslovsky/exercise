#include "slic.hxx"
#include <iostream>
#include <algorithm>

using namespace std;

int main() {
  int k = 2;
  int data[10] = {1,2,3,4,5,6,7,8,9,37};
  int clusters[k];
  int labels[10] = {0};
  L2SquaredArray<int> l2;
  KMeans<int, L2SquaredArray<int> > km(l2, k);
  km.infer(data, 10, 1, labels, clusters);
  for (int i = 0; i < 10; i++) {
    cout << labels[i] << "\n";
  }
  cout << "\n";
  for (int i = 0; i < k; i++) {
    cout << clusters[i] << "\n";
  }
  return 0;
}
