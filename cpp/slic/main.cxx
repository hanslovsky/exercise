#include "slic.hxx"
#include <iostream>
#include <algorithm>

using namespace std;

int main() {
  int k = 2;
  int data[10] = {3,7,2,5,6,37,1,4,9,8};
  int clusters[k];
  int labels[10] = {0};
  L2SquaredArray<int> l2;
  KMeans<int, L2SquaredArray<int> > km(l2, k);
  km.infer(data, 10, 1, labels, clusters);
  std::cout << "bla\n" << std::endl;
  for (int i = 0; i < 10; i++) {
    cout << labels[i] << "\n";
  }
  cout << "\n";
  for (int i = 0; i < k; i++) {
    cout << clusters[i] << "\n";
  }
  return 0;
}
