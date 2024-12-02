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
    Node *left, *right;

    Node() : key(0), value(0), left(nullptr), right(nullptr) {}
    Node(K k, V v) : key(k), value(v), left(nullptr), right(nullptr) {}
    Node(const Node & rhs) :
        key(rhs.key), value(rhs.value), left(nullptr), right(nullptr) {}
  };

  Node * root;

  void clear(Node * node) {
    if (!node)
      return;
    clear(node->left);
    clear(node->right);
    delete node;
  }

  Node * remove(Node * node, K key) {
    if (!node)
      return nullptr;
    if (key == node->key) {
      if (!node->left && !node->right) {
        delete node;
        return nullptr;
      }
      if (!node->left) {
        Node * temp = node->right;
        delete node;
        return temp;
      }
      if (!node->right) {
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
    while (node) {
      if (key == node->key)
        return node;
      node = key > node->key ? node->right : node->left;
    }
    return nullptr;
  }

  Node * copy(Node * node) const {
    if (!node)
      return nullptr;
    Node * newNode = new Node(*node);
    newNode->left = copy(node->left);
    newNode->right = copy(node->right);
    return newNode;
  }

 public:
  BstMap() : root(nullptr) {}

  BstMap(const BstMap & rhs) : root(copy(rhs.root)) {}

  BstMap & operator=(const BstMap & rhs) {
    if (this != &rhs) {
      Node * newRoot = copy(rhs.root);
      clear(root);
      root = newRoot;
    }
    return *this;
  }

  void add(const K & key, const V & value) override {
    Node ** node = &root;
    while (*node) {
      if ((*node)->key == key) {
        (*node)->value = value;
        return;
      }
      node = key > (*node)->key ? &(*node)->right : &(*node)->left;
    }
    *node = new Node(key, value);
  }

  const V & lookup(const K & key) const override {
    Node * node = find(root, key);
    if (!node)
      throw std::invalid_argument("key not found");
    return node->value;
  }

  void remove(const K & key) override {
    Node * node = find(root, key);
    if (!node)
      return;
    if (node->left && node->right) {
      Node * swapNode = node->left;
      while (swapNode->right)
        swapNode = swapNode->right;
      std::swap(node->key, swapNode->key);
      std::swap(node->value, swapNode->value);
    }
    root = remove(root, key);
  }

  ~BstMap() override { clear(root); }
};
