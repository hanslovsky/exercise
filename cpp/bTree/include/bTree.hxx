#ifndef BTREE_HXX
#define BTREE_HXX

#include <iostream>
#include <vector>
#include <stack>
#include <utility>
#include <deque>

template <class Key, class Data>
class BTree {
public:
  struct Node {
    Key key_;
    Data data_;
    Node *left_;
    Node *right_;
    Node(Key key, Data data, Node* left = NULL, Node* right = NULL) :
      key_(key),
      data_(data),
      left_(left),
      right_(right)
    {}
    ~Node();
  };
private:
  Node *root_;
public:
  BTree();
  BTree(Key key, Data data);
  ~BTree();

  bool addData(Key key, Data data);
  Data getData(Key key);
  int getDepth();
  void treeToVectorInOrder(std::vector<std::pair<Key, Data> > &output);
  Node* getRoot();
};


template <class Key, class Data>
BTree<Key, Data>::Node::~Node() {
  std::deque<Node*> nodeDeque;
  nodeDeque.push_back(this);
  while(nodeDeque.empty() == 0) {
    Node *curr = nodeDeque.front();
    nodeDeque.pop_front();
    if (curr) {
      nodeDeque.push_back(curr->left_);
      nodeDeque.push_back(curr->right_);
      curr->left_ = 0;
      curr->right_ = 0;
      if (curr != this) {
	// std::cout << "deleting Node " << curr->key_ << std::endl;
	delete curr;
      }
    }
  }
  // std::cout<< "deleting Node " << this->key_ << std::endl;
}

template <class Key, class Data>
BTree<Key, Data>::BTree() : root_( NULL ) {} 

template <class Key, class Data>
BTree<Key, Data>::BTree(Key key, Data data) {
  root_ = new Node(key, data);
}

template <class Key, class Data>
BTree<Key, Data>::~BTree() {
  delete root_;
}

template <class Key, class Data>
bool BTree<Key, Data>::addData(Key key, Data data) {
  if (root_ == 0) {
    root_ = new Node(key, data);
    return true;
  }
  Node *node = root_;
  while (true) {
    if (key == node->key_) {
      return false;
    }
    else {
      if (key < node->key_) {
	if (node->left_ == 0) {
	  node->left_ = new Node(key, data);
	  break;
	}
	else {
	  node = node->left_;
	}
      }
      else {
	if (node->right_ == 0) {
	  node->right_ = new Node(key, data);
	  break;
	}
	else {
	  node = node->right_;
	}
      }
    }
  }
  return true;
}

template <class Key, class Data>
Data BTree<Key, Data>::getData(Key key) {
  Node *node = root_;
  while (node != 0) {
    if (key == node->key_) {
      return node->data_;
    }
    else {
      if (key < node->key_) {
	node = node->left_;
      }
      else {
	node = node->right_;
      }
    }
  }
  throw 1;
}

template <class Key, class Data>
int BTree<Key, Data>::getDepth() {
  int depth = 0;
  Node *node = root_;
  Node *prev = 0;
  std::stack<Node*> nodeStack;
  nodeStack.push(node);
  while (nodeStack.empty() == false) {
    Node *curr = nodeStack.top();
    if (prev == 0 || prev->left_ == curr || prev->right_ == curr) {
      if (curr->left_)
	nodeStack.push(curr->left_);
      else if (curr->right_)
	nodeStack.push(curr->right_);
    }
    else if (curr->left_ == prev) {
      if (curr->right_)
	nodeStack.push(curr->right_);
    }
    else
      nodeStack.pop();
    prev = curr;
    if (nodeStack.size() > depth)
      depth = nodeStack.size();
  }
  return depth;
}

template <class Key, class Data>
void BTree<Key, Data>::treeToVectorInOrder(std::vector<std::pair<Key, Data> > &output) {
  Node *node = root_;
  std::stack<Node*> nodeStack;
  while (true) {
    if (node != 0) {
      nodeStack.push(node);
      node = node->left_;
    }
    else {
      if (nodeStack.empty()) {
	break;
      }
      else {
	node = nodeStack.top();
	nodeStack.pop();
	output.push_back(std::make_pair(node->key_, node->data_));
	node = node->right_;
      }
    }
  }
}
  
template <class Key, class Data>
typename BTree<Key, Data>::Node* BTree<Key, Data>::getRoot() {
  return root_;
}

#endif
