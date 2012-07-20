#include <iostream>
#include <vector>
#include <stack>
#include <utility>

template <class Key, class Data>
class BTree {
  struct Node {
    Key _key;
    Data _data;
    Node *_left;
    Node *_right;
    Node(Key key, Data data, Node* left = NULL, Node* right = NULL) :
      _key(key),
      _data(data),
      _left(left),
      _right(right)
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
    if (key == node->_key) {
      return false;
    }
    else {
      if (key < node->_key) {
	if (node->_left == NULL) {
	  node->_left = new Node(key, data);
	  break;
	}
	else {
	  node = node->_left;
	}
      }
      else {
	if (node->_right == NULL) {
	  node->_right = new Node(key, data);
	  break;
	}
	else {
	  node = node->_right;
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
    if (key == node->_key) {
      return node->_data;
    }
    else {
      if (key < node->_key) {
	node = node->_left;
      }
      else {
	node = node->_right;
      }
    }
  }
  throw 1;
}

/*template <class Key, class Data>
int Btree<Key, Data>::getDepth() {
  int depth = 0;
  Node *node = _root;
  std::stack<Node*> nodeStack;
  while (true) {
    if (node != NULL) {
      nodeStack.push(node);
      node = node->left;
    }
    else {
      if (nodeStack.empty()) {
	break;
      }
      else node = nodeStack.top();
      nodeStack.pop();
    
  }
  if 
  }*/

template <class Key, class Data>
void BTree<Key, Data>::treeToVectorInOrder(std::vector<std::pair<Key, Data> > &output) {
  Node *node = _root;
  std::stack<Node*> nodeStack;
  while (true) {
    if (node != NULL) {
      nodeStack.push(node);
      node = node->_left;
    }
    else {
      if (nodeStack.empty()) {
	break;
      }
      else {
	node = nodeStack.top();
	nodeStack.pop();
	output.push_back(std::make_pair(node->_key, node->_data));
	node = node->_right;
      }
    }
  }
}
  


