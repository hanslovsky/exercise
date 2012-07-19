#include <iostream>

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
};

template <class Key, class Data>
BTree<Key, Data>::BTree() : _root( NULL ) {} 

template <class Key, class Data>
BTree<Key, Data>::BTree(Key key, Data data) {
  _root = new Node(key, data);
}

template <class Key, class Data>
bool BTree<Key, Data>::addData(Key key, Data data) {
  Node *node = _root;
  if (node == NULL) {
    node = new Node(key, data);
    return true;
  }
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
