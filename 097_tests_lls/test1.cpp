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
    assert(il.head != NULL && il.tail != NULL);
    assert(il.head->data == 5 && il.tail->data == 5);
    assert(il.head == il.tail);
    assert(il.getSize() == 1);

    il.addFront(10);
    il.addFront(15);
    assert(il.head->data == 15);
    assert(il.head->next->data == 10);
    assert(il.tail->data == 5);
    assert(il.getSize() == 3);
  }

  void testAddBack() {
    IntList il;
    il.addBack(5);
    assert(il.head != NULL && il.tail != NULL);
    assert(il.head->data == 5 && il.tail->data == 5);
    assert(il.head == il.tail);
    assert(il.getSize() == 1);

    il.addBack(10);
    il.addBack(15);
    assert(il.head->data == 5);
    assert(il.head->next->data == 10);
    assert(il.tail->data == 15);
    assert(il.getSize() == 3);
  }

  void testRemove() {
    IntList il;
    il.addBack(5);
    il.addBack(10);
    il.addBack(15);
    il.addBack(20);

    assert(il.remove(5) == true);
    assert(il.head->data == 10);
    assert(il.head->prev == NULL);
    assert(il.getSize() == 3);

    assert(il.remove(20) == true);
    assert(il.tail->data == 15);
    assert(il.tail->next == NULL);
    assert(il.getSize() == 2);

    assert(il.remove(10) == true);
    assert(il.head->data == 15);
    assert(il.head == il.tail);
    assert(il.getSize() == 1);

    assert(il.remove(99) == false);
    assert(il.getSize() == 1);
  }

  void testDestructor() {
    IntList * il = new IntList();
    il->addBack(1);
    il->addBack(2);
    delete il;
  }

  void testCopyConstructor() {
    IntList il;
    il.addBack(1);
    il.addBack(2);
    il.addBack(3);

    IntList copy(il);
    assert(copy.getSize() == 3);
    assert(copy[0] == 1 && copy[1] == 2 && copy[2] == 3);

    il.addFront(0);
    assert(copy.getSize() == 3);
    assert(copy[0] == 1 && copy[1] == 2 && copy[2] == 3);
  }

  void testAssignmentOperator() {
    IntList il;
    il.addBack(1);
    il.addBack(2);

    IntList assigned;
    assigned = il;
    assert(assigned.getSize() == 2);
    assert(assigned[0] == 1 && assigned[1] == 2);

    il.addBack(3);
    assert(assigned.getSize() == 2);
    assert(assigned[0] == 1 && assigned[1] == 2);
  }

  // New test for self-assignment
  void testSelfAssignment() {
    IntList il;
    il.addBack(1);
    il.addBack(2);

    il = il;  // Self-assignment check
    assert(il.getSize() == 2);
    assert(il[0] == 1 && il[1] == 2);
  }

  // New test for clearing a list after assignment
  void testClearAfterAssignment() {
    IntList il;
    il.addBack(1);
    il.addBack(2);

    IntList assigned = il;
    assigned.addBack(3);

    // Clear original list and verify assigned list remains unchanged
    il.remove(1);
    il.remove(2);
    assert(assigned.getSize() == 3);
    assert(assigned[0] == 1 && assigned[1] == 2 && assigned[2] == 3);
  }

  void testOperatorSquareBrackets() {
    IntList il;
    il.addBack(5);
    il.addBack(10);
    il.addBack(15);

    assert(il[0] == 5);
    assert(il[1] == 10);
    assert(il[2] == 15);

    try {
      il[3];
      assert(false);
    }
    catch (const std::exception & e) {
      assert(true);
    }
  }

  void testFind() {
    IntList il;
    il.addBack(5);
    il.addBack(10);
    il.addBack(15);

    assert(il.find(5) == 0);
    assert(il.find(10) == 1);
    assert(il.find(15) == 2);
    assert(il.find(20) == -1);
  }

  void testGetSize() {
    IntList il;
    assert(il.getSize() == 0);

    il.addBack(5);
    assert(il.getSize() == 1);

    il.addBack(10);
    assert(il.getSize() == 2);

    il.remove(5);
    assert(il.getSize() == 1);

    il.remove(10);
    assert(il.getSize() == 0);
  }

  void testSequentialOperations() {
    IntList il;
    il.addFront(10);
    il.addBack(20);
    il.addFront(5);
    il.remove(10);

    assert(il.head->data == 5);
    assert(il.tail->data == 20);
    assert(il.getSize() == 2);
    assert(il.head->next == il.tail);
    assert(il.tail->prev == il.head);
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
  t.testSelfAssignment();
  t.testClearAfterAssignment();
  t.testOperatorSquareBrackets();
  t.testFind();
  t.testGetSize();
  t.testSequentialOperations();

  std::cout << "All tests passed!" << std::endl;
  return EXIT_SUCCESS;
}
