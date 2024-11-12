#include <assert.h>

#include <cstdlib>
#include <iostream>

#include "il.hpp"

class Tester {
 public:
  // Testing for default constructor is done for you
  void testDefCtor() {
    IntList il;
    assert(il.head == NULL);
    assert(il.tail == NULL);
    assert(il.getSize() == 0);
  }

  // Test for addFront
  void testAddFront() {
    IntList il;

    // Test adding to an empty list
    il.addFront(5);
    assert(il.head->data == 5);
    assert(il.tail->data == 5);
    assert(il.head == il.tail);  // Head and tail should be the same for one item
    assert(il.getSize() == 1);

    // Test adding to a non-empty list
    il.addFront(10);
    assert(il.head->data == 10);
    assert(il.head->next->data == 5);
    assert(il.tail->data == 5);
    assert(il.getSize() == 2);

    il.addFront(15);
    assert(il.head->data == 15);
    assert(il.head->next->data == 10);
    assert(il.tail->data == 5);
    assert(il.getSize() == 3);
  }

  // Test for addBack
  void testAddBack() {
    IntList il;

    // Test adding to an empty list
    il.addBack(5);
    assert(il.head->data == 5);
    assert(il.tail->data == 5);
    assert(il.head == il.tail);  // Head and tail should be the same for one item
    assert(il.getSize() == 1);

    // Test adding to a non-empty list
    il.addBack(10);
    assert(il.head->data == 5);
    assert(il.tail->data == 10);
    assert(il.head->next->data == 10);
    assert(il.tail->prev->data == 5);
    assert(il.getSize() == 2);

    il.addBack(15);
    assert(il.head->data == 5);
    assert(il.tail->data == 15);
    assert(il.head->next->data == 10);
    assert(il.head->next->next->data == 15);
    assert(il.tail->prev->data == 10);
    assert(il.getSize() == 3);
  }

  // Test for remove
  void testRemove() {
    IntList il;
    il.addBack(5);
    il.addBack(10);
    il.addBack(15);
    il.addBack(20);

    // Test removing head
    assert(il.remove(5) == true);
    assert(il.head->data == 10);
    assert(il.head->prev == NULL);  // Head's previous should be NULL
    assert(il.getSize() == 3);

    // Test removing tail
    assert(il.remove(20) == true);
    assert(il.tail->data == 15);
    assert(il.tail->next == NULL);  // Tail's next should be NULL
    assert(il.getSize() == 2);

    // Test removing middle
    assert(il.remove(10) == true);
    assert(il.head->data == 15);
    assert(il.head == il.tail);  // Only one element left
    assert(il.getSize() == 1);

    // Test removing non-existent element
    assert(il.remove(99) == false);
    assert(il.getSize() == 1);
  }

  // Test for copy constructor
  void testCopyConstructor() {
    IntList il;
    il.addBack(1);
    il.addBack(2);
    il.addBack(3);

    IntList copy(il);
    assert(copy.getSize() == 3);
    assert(copy.head->data == 1);
    assert(copy.head->next->data == 2);
    assert(copy.tail->data == 3);
    assert(copy[0] == 1);
    assert(copy[1] == 2);
    assert(copy[2] == 3);

    // Modify original and verify copy remains unchanged
    il.addFront(0);
    assert(copy.getSize() == 3);
    assert(copy[0] == 1);
  }

  // Test for assignment operator
  void testAssignmentOperator() {
    IntList il;
    il.addBack(1);
    il.addBack(2);

    IntList copy;
    copy = il;
    assert(copy.getSize() == 2);
    assert(copy.head->data == 1);
    assert(copy.tail->data == 2);

    // Modify original and verify copy remains unchanged
    il.addFront(0);
    assert(copy.getSize() == 2);
    assert(copy.head->data == 1);
  }

  // Test for operator[]
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
      assert(false);  // Should throw an exception
    }
    catch (const std::exception & e) {
      assert(true);  // Exception caught as expected
    }
  }

  // Test for find
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

  // Test for getSize
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
};

int main(void) {
  Tester t;
  t.testDefCtor();
  t.testAddFront();
  t.testAddBack();
  t.testRemove();
  t.testCopyConstructor();
  t.testAssignmentOperator();
  t.testOperatorSquareBrackets();
  t.testFind();
  t.testGetSize();

  std::cout << "All tests passed!" << std::endl;
  return EXIT_SUCCESS;
}
