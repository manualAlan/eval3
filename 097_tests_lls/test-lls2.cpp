#include <assert.h>

#include <cstdlib>
#include <iostream>

#include "il.hpp"

class Tester {
 public:
  void testDefCtor() {
    IntList il;
    assert(il.head == NULL);
    assert(il.tail == NULL);
    assert(il.getSize() == 0);
  }

  void testAddFront() {
    IntList il;
    il.addFront(5);
    assert(il.head->data == 5 && il.tail->data == 5 && il.getSize() == 1);
    il.addFront(10);
    assert(il.head->data == 10 && il.head->next->data == 5 && il.getSize() == 2);
  }

  void testAddBack() {
    IntList il;
    il.addBack(5);
    assert(il.head->data == 5 && il.tail->data == 5 && il.getSize() == 1);
    il.addBack(10);
    assert(il.tail->data == 10 && il.head->next->data == 10 && il.getSize() == 2);
  }

  void testRemove() {
    IntList il;
    il.addBack(5);
    il.addBack(10);
    il.remove(5);
    assert(il.head->data == 10 && il.tail->data == 10 && il.getSize() == 1);
  }

  void testDestructor() {
    IntList * il = new IntList();
    il->addBack(1);
    il->addBack(2);
    delete il;  // Test should pass if no memory leaks occur and no crashes
  }

  void testCopyConstructor() {
    IntList il;
    il.addBack(1);
    il.addBack(2);
    IntList copy(il);
    assert(copy.getSize() == 2 && copy[0] == 1 && copy[1] == 2);
    copy.addBack(3);
    assert(il.getSize() == 2 && copy.getSize() == 3);
  }

  void testAssignmentOperator() {
    IntList il;
    il.addBack(1);
    il.addBack(2);
    IntList assigned;
    assigned = il;
    assert(assigned.getSize() == 2 && assigned[0] == 1 && assigned[1] == 2);
    assigned.addBack(3);
    assert(il.getSize() == 2 && assigned.getSize() == 3);
  }

  void testOperatorSquareBrackets() {
    IntList il;
    il.addBack(5);
    il.addBack(10);
    assert(il[0] == 5 && il[1] == 10);
  }

  void testFind() {
    IntList il;
    il.addBack(5);
    il.addBack(10);
    assert(il.find(5) == 0 && il.find(10) == 1 && il.find(20) == -1);
  }

  void testGetSize() {
    IntList il;
    il.addBack(5);
    assert(il.getSize() == 1);
    il.addBack(10);
    assert(il.getSize() == 2);
  }
};

int main() {
  Tester t;
  t.testDefCtor();
  t.testAddFront();
  t.testAddBack();
  t.testRemove();
  t.testDestructor();
  t.testCopyConstructor();
  t.testAssignmentOperator();
  t.testOperatorSquareBrackets();
  t.testFind();
  t.testGetSize();

  std::cout << "All tests passed!" << std::endl;
  return EXIT_SUCCESS;
}
