#include "include/bTree.hxx"
#include <iostream>

using namespace std;


int main() {
  int k = 5;
  int d = 3;
  BTree<int, int> Tree1;
  BTree<int, int> Tree2(k, d);
  cout << Tree2.getData(5) << endl;
  cout << Tree2.addData(3, 5) << endl;
  cout << Tree2.addData(3, 5) << endl;
  cout << Tree1.addData(1, 2) << endl;
  cout << Tree1.getData(3) << endl;
}
