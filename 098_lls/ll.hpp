#ifndef __LL_HPP__
#define __LL_HPP__

#include <assert.h>

#include <cstdlib>
#include <exception>
template<typename T>
class LinkedList {
 private:
  class Node {
   public:
    T data;
    Node * next;
    Node * prev;

    Node() : data(0), next(NULL), prev(NULL) {}
    Node(T d) : data(d), next(NULL), prev(NULL) {}
    Node(T d, Node * n, Node * p) : data(d), next(n), prev(p) {}
  };

  Node * head;
  Node * tail;
  int size;

  void deleteNodes(Node * node) {
    while (node) {
      Node * tmp = node->next;
      delete node;
      node = tmp;
    }
  }

  Node * copyNodes(Node * node) {
    if (node == NULL)
      return NULL;
    Node * newHead = new Node(node->data);
    Node * prevNew = newHead;
    node = node->next;
    while (node) {
      Node * newNode = new Node(node->data);
      prevNew->next = newNode;
      newNode->prev = prevNew;
      prevNew = newNode;
      node = node->next;
    }
    return newHead;
  }

 public:
  LinkedList() : head(NULL), tail(NULL), size(0) {}

  LinkedList(const LinkedList & rhs) : head(NULL), tail(NULL), size(0) {
    Node * node = rhs.head;
    while (node) {
      addBack(node->data);
      node = node->next;
    }
  }

  LinkedList & operator=(const LinkedList & rhs) {
    if (this != &rhs) {
      Node * tempHead = NULL;
      Node * tempTail = NULL;
      size = rhs.size;
      if (size > 0)
        tempHead = copyNodes(rhs.head);
      Node * node = tempHead;
      while (node) {
        tempTail = node;
        node = node->next;
      }
      deleteNodes(head);
      head = tempHead;
      tail = tempTail;
    }
    return *this;
  }

  ~LinkedList() { deleteNodes(head); }

  void addFront(const T & item) {
    Node * node = new Node(item);
    if (size == 0) {
      head = tail = node;
    }
    else {
      node->next = head;
      head->prev = node;
      head = node;
    }
    size++;
  }

  void addBack(const T & item) {
    Node * node = new Node(item);
    if (size == 0) {
      head = tail = node;
    }
    else {
      tail->next = node;
      node->prev = tail;
      tail = node;
    }
    size++;
  }

  bool remove(const T & item) {
    int idx = find(item);
    if (idx < 0)
      return false;
    Node * node = head;
    while (idx-- > 0)
      node = node->next;
    if (node->prev)
      node->prev->next = node->next;
    if (node->next)
      node->next->prev = node->prev;
    if (node == head)
      head = node->next;
    if (node == tail)
      tail = node->prev;
    delete node;
    size--;
    return true;
  }

  T & operator[](int index) {
    if (index < 0 || index >= size)
      throw std::out_of_range("invalid index");
    Node * node = head;
    while (index-- > 0)
      node = node->next;
    return node->data;
  }

  const T & operator[](int index) const {
    if (index < 0 || index >= size)
      throw std::out_of_range("invalid index");
    Node * node = head;
    while (index-- > 0)
      node = node->next;
    return node->data;
  }

  int find(const T & item) {
    Node * node = head;
    int idx = 0;
    while (node) {
      if (node->data == item)
        return idx;
      node = node->next;
      idx++;
    }
    return -1;
  }

  int getSize() const { return size; }

  friend class Tester;
};
//YOUR CODE GOES HERE

#endif
