#include <iostream>
#include <vector>
#include <stack>
#include <utility>

template <class Key, class Data>
class BTree {
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
  Node *_root;
public:
  BTree();
  BTree(Key key, Data data);
  //  ~BTree();

  bool addData(Key key, Data data);
  Data getData(Key key);
  int getDepth();
  void treeToVectorInOrder(std::vector<std::pair<Key, Data> > &output);
};




template <class Key, class Data>
BTree<Key, Data>::BTree() : _root( NULL ) {} 

template <class Key, class Data>
BTree<Key, Data>::BTree(Key key, Data data) {
  _root = new Node(key, data);
}

template <class Key, class Data>
bool BTree<Key, Data>::addData(Key key, Data data) {
  if (_root == NULL) {
    _root = new Node(key, data);
    return true;
  }
  Node *node = _root;
  while (true) {
    if (key == node->key_) {
      return false;
    }
    else {
      if (key < node->key_) {
	if (node->left_ == NULL) {
	  node->left_ = new Node(key, data);
	  break;
	}
	else {
	  node = node->left_;
	}
      }
      else {
	if (node->right_ == NULL) {
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
  Node *node = _root;
  while (node != NULL) {
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
  Node *node = _root;
  Node *prev = NULL;
  std::stack<Node*> nodeStack;
  nodeStack.push(node);
  while (nodeStack.empty() == false) {
    Node *curr = nodeStack.top();
    if (prev == NULL || prev->left_ == curr || prev->right_ == curr) {
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
  Node *node = _root;
  std::stack<Node*> nodeStack;
  while (true) {
    if (node != NULL) {
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
  


