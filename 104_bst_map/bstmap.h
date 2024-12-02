#include <iostream>
#include <stdexcept>
#include <vector>

#include "map.h"

template<typename K, typename V>
class BstMap : public Map<K, V> {
 private:
  class Node {
   public:
    K key;
    V value;
    Node * left;
    Node * right;
    Node() : key(0), value(0), left(NULL), right(NULL) {}
    Node(K k, V v) : key(k), value(v), left(NULL), right(NULL) {}
    Node(const Node & rhs) : key(rhs.key), value(rhs.value), left(NULL), right(NULL) {}
  };

  Node * root;

  void removeNodes(Node * node) {
    if (node == NULL)
      return;
    removeNodes(node->left);
    removeNodes(node->right);
    delete node;
  }

  Node * removeNode(Node * node, K key) {
    if (node == NULL)
      return NULL;
    if (key == node->key) {
      if (node->left == NULL && node->right == NULL) {
        delete node;
        return NULL;
      }
      if (node->left == NULL) {
        Node * tmp = node->right;
        delete node;
        return tmp;
      }
      if (node->right == NULL) {
        Node * tmp = node->left;
        delete node;
        return tmp;
      }
    }
    node->left = removeNode(node->left, key);
    node->right = removeNode(node->right, key);
    return node;
  }

  Node * findNode(const K & key) {
    Node ** nodePtr = &root;
    while (*nodePtr != NULL) {
      if ((*nodePtr)->key == key)
        return *nodePtr;
      nodePtr = (key > (*nodePtr)->key) ? &((*nodePtr)->right) : &((*nodePtr)->left);
    }
    return NULL;
  }

  void printNode(Node * node) const {
    if (node == NULL)
      return;
    std::cout << node->key << " ";
    printNode(node->left);
    printNode(node->right);
  }

  Node * copyNodes(Node * node) const {
    if (node == NULL)
      return NULL;
    Node * newNode = new Node(*node);
    newNode->left = copyNodes(node->left);
    newNode->right = copyNodes(node->right);
    return newNode;
  }

 public:
  BstMap() : root(NULL) {}
  BstMap(const BstMap & rhs) : root(NULL) { root = copyNodes(rhs.root); }
  BstMap & operator=(const BstMap & rhs) {
    if (&rhs != this) {
      Node * newRoot = copyNodes(rhs.root);
      removeNodes(root);
      root = newRoot;
    }
    return *this;
  }

  virtual void add(const K & key, const V & value) {
    Node ** nodePtr = &root;
    while (true) {
      if (*nodePtr == NULL) {
        *nodePtr = new Node(key, value);
        return;
      }
      if ((*nodePtr)->key == key) {
        (*nodePtr)->value = value;
        return;
      }
      nodePtr = (key > (*nodePtr)->key) ? &((*nodePtr)->right) : &((*nodePtr)->left);
    }
  }

  virtual const V & lookup(const K & key) const throw(std::invalid_argument) {
    Node * const * nodePtr = &root;
    while (*nodePtr != NULL) {
      if ((*nodePtr)->key == key)
        return (*nodePtr)->value;
      nodePtr = (key > (*nodePtr)->key) ? &((*nodePtr)->right) : &((*nodePtr)->left);
    }
    throw std::invalid_argument("key not found");
  }

  virtual void remove(const K & key) {
    Node * node = findNode(key);
    if (node == NULL)
      return;
    if (node->left && node->right) {
      Node * swapNode = node->left;
      while (swapNode->right) {
        swapNode = swapNode->right;
      }
      std::swap(node->key, swapNode->key);
      std::swap(node->value, swapNode->value);
      node = swapNode;
    }
    root = removeNode(root, key);
  }

  virtual ~BstMap() { removeNodes(root); }
};
