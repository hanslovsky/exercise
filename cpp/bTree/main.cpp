#include "include/bTree.hxx"
#include <iostream>
#include <vector>
#include <utility>
#include <stdlib.h>

using namespace std;


int main() {
  int k = 5;
  int d = 3;
  BTree<int, int> Tree1;
  BTree<int, int> Tree2(k, d);
  cout << Tree2.getData(5) << endl;
  cout << Tree2.addData(3, 5) << endl;
  cout << Tree2.addData(3, 5) << endl;
  cout << Tree2.getData(3) << endl;
  cout << Tree1.addData(1, 2) << endl;
  cout << Tree1.getData(1) << endl;
  cout << Tree2.addData(1, 2) << endl;
  cout << Tree2.addData(7, 3) << endl;
  cout << Tree2.addData(6, 2) << endl;
  cout << Tree2.addData(4, 10) << endl;
  for (int i = 0; i < 1; i++) {
    Tree2.addData(rand(), rand());
  }
  vector<pair<int, int> > output;
  Tree2.treeToVectorInOrder(output);
  cout << endl;
  for (vector<pair<int, int> >::iterator it = output.begin(); it != output.end(); it++) {
      cout << "Key: "<< it->first << ", Value: " << it->second << endl;
  }
  cout << Tree2.getDepth() << endl;
  /*BTree<int, int>::Node* rt = Tree2.getRoot();
  cout << rt->data_ << "  " << rt->left_->data_ << endl;
  cout << Tree2.getDepth() << endl;*/
  Tree2.rotateRight(3);
  output.erase(output.begin(), output.end());
  Tree2.treeToVectorInOrder(output);
  cout << endl;
  for (vector<pair<int, int> >::iterator it = output.begin(); it != output.end(); it++) {
      cout << "Key: "<< it->first << ", Value: " << it->second << endl;
  }
  cout << Tree2.getDepth() << endl;

  Tree2.rotateLeft(1);
  output.erase(output.begin(), output.end());
  Tree2.treeToVectorInOrder(output);
  cout << endl;
  for (vector<pair<int, int> >::iterator it = output.begin(); it != output.end(); it++) {
      cout << "Key: "<< it->first << ", Value: " << it->second << endl;
  }
  cout << Tree2.getDepth() << endl;
}
