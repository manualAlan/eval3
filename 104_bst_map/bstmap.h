#include <iostream>
#include <stdexcept>
#include <vector>

#include "map.h"

template<typename K, typename V>
class BstMap : public Map<K, V> {
 private:
  struct Node {
    K key;
    V value;
    Node * left;
    Node * right;

    Node() : key(0), value(0), left(NULL), right(NULL) {}
    Node(K k, V v) : key(k), value(v), left(NULL), right(NULL) {}
    Node(const Node & rhs) : key(rhs.key), value(rhs.value), left(NULL), right(NULL) {}
  };

  Node * root;

  void clear(Node * node) {
    if (node == NULL)
      return;
    clear(node->left);
    clear(node->right);
    delete node;
  }

  Node * remove(Node * node, K key) {
    if (node == NULL)
      return NULL;
    if (key == node->key) {
      if (node->left == NULL && node->right == NULL) {
        delete node;
        return NULL;
      }
      if (node->left == NULL) {
        Node * temp = node->right;
        delete node;
        return temp;
      }
      if (node->right == NULL) {
        Node * temp = node->left;
        delete node;
        return temp;
      }
    }
    node->left = remove(node->left, key);
    node->right = remove(node->right, key);
    return node;
  }

  Node * find(Node * node, const K & key) const {
    while (node != NULL) {
      if (key == node->key)
        return node;
      node = (key > node->key) ? node->right : node->left;
    }
    return NULL;
  }

  Node * copy(Node * node) const {
    if (node == NULL)
      return NULL;
    Node * newNode = new Node(*node);
    newNode->left = copy(node->left);
    newNode->right = copy(node->right);
    return newNode;
  }

 public:
  BstMap() : root(NULL) {}

  BstMap(const BstMap & rhs) : root(copy(rhs.root)) {}

  BstMap & operator=(const BstMap & rhs) {
    if (this != &rhs) {
      Node * newRoot = copy(rhs.root);
      clear(root);
      root = newRoot;
    }
    return *this;
  }

  void add(const K & key, const V & value) {
    Node ** node = &root;
    while (*node != NULL) {
      if ((*node)->key == key) {
        (*node)->value = value;
        return;
      }
      node = (key > (*node)->key) ? &(*node)->right : &(*node)->left;
    }
    *node = new Node(key, value);
  }

  const V & lookup(const K & key) const throw(std::invalid_argument) {
    Node * node = find(root, key);
    if (node == NULL)
      throw std::invalid_argument("key not found");
    return node->value;
  }

  void remove(const K & key) {
    Node * node = find(root, key);
    if (node == NULL)
      return;
    if (node->left != NULL && node->right != NULL) {
      Node * swapNode = node->left;
      while (swapNode->right != NULL)
        swapNode = swapNode->right;
      K tempKey = node->key;
      V tempValue = node->value;
      node->key = swapNode->key;
      node->value = swapNode->value;
      swapNode->key = tempKey;
      swapNode->value = tempValue;
    }
    root = remove(root, key);
  }

  ~BstMap() { clear(root); }
};
