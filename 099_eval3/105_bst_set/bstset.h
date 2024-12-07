#include <iostream>
#include <stdexcept>
#include <vector>

#include "set.h"

template<typename T>
class BstSet : public Set<T> {
 private:
  struct Node {
    T key;
    Node * left;
    Node * right;

    Node() : key(0), left(NULL), right(NULL) {}
    Node(T k) : key(k), left(NULL), right(NULL) {}
    Node(const Node & rhs) : key(rhs.key), left(NULL), right(NULL) {}
  };

  Node * root;

  void freeTree(Node * node) {
    if (node == NULL)
      return;
    freeTree(node->left);
    freeTree(node->right);
    delete node;
  }

  Node * deleteNode(Node * node, T key) {
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
    node->left = deleteNode(node->left, key);
    node->right = deleteNode(node->right, key);
    return node;
  }

  Node * search(Node * node, const T & key) const {
    while (node != NULL) {
      if (key == node->key)
        return node;
      node = (key > node->key) ? node->right : node->left;
    }
    return NULL;
  }

  Node * cloneTree(Node * node) const {
    if (node == NULL)
      return NULL;
    Node * newNode = new Node(node->key);
    newNode->left = cloneTree(node->left);
    newNode->right = cloneTree(node->right);
    return newNode;
  }

 public:
  BstSet() : root(NULL) {}

  BstSet(const BstSet & rhs) : root(cloneTree(rhs.root)) {}

  BstSet & operator=(const BstSet & rhs) {
    if (this != &rhs) {
      Node * newRoot = cloneTree(rhs.root);
      freeTree(root);
      root = newRoot;
    }
    return *this;
  }

  void add(const T & key) {
    Node ** current = &root;
    while (*current != NULL) {
      if ((*current)->key == key)
        return;
      current = (key > (*current)->key) ? &(*current)->right : &(*current)->left;
    }
    *current = new Node(key);
  }

  bool contains(const T & key) const { return search(root, key) != NULL; }

  void remove(const T & key) {
    Node * target = search(root, key);
    if (target == NULL)
      return;

    if (target->left != NULL && target->right != NULL) {
      Node * maxLeft = target->left;
      while (maxLeft->right != NULL)
        maxLeft = maxLeft->right;
      T tempKey = target->key;
      target->key = maxLeft->key;
      maxLeft->key = tempKey;
    }
    root = deleteNode(root, key);
  }

  ~BstSet() { freeTree(root); }
};
