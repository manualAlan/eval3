#include <assert.h>

#include <cstdlib>
#include <iostream>

#include "il.hpp"

class Tester {
 public:
  // Basic tests for the default constructor
  void testDefCtor() {
    IntList il;
    assert(il.head == NULL);
    assert(il.tail == NULL);
    assert(il.getSize() == 0);
  }

  // Tests for addFront operation
  void testAddFront() {
    IntList il;

    // Add to an empty list
    il.addFront(5);
    assert(il.head != NULL && il.tail != NULL);
    assert(il.head->data == 5 && il.tail->data == 5);
    assert(il.head == il.tail);
    assert(il.getSize() == 1);

    // Add multiple items to the front, verify pointer connections
    il.addFront(10);
    assert(il.head->data == 10 && il.head->next->data == 5);
    assert(il.tail->data == 5 && il.tail->prev == il.head);
    assert(il.getSize() == 2);

    il.addFront(15);
    assert(il.head->data == 15 && il.head->next->data == 10);
    assert(il.tail->data == 5 && il.tail->prev->data == 10);
    assert(il.getSize() == 3);
  }

  // Tests for addBack operation
  void testAddBack() {
    IntList il;

    // Add to an empty list
    il.addBack(5);
    assert(il.head != NULL && il.tail != NULL);
    assert(il.head->data == 5 && il.tail->data == 5);
    assert(il.head == il.tail);
    assert(il.getSize() == 1);

    // Add multiple items to the back, verify pointer connections
    il.addBack(10);
    assert(il.head->data == 5);
    assert(il.head->next->data == 10 && il.tail->data == 10);
    assert(il.tail->prev->data == 5);
    assert(il.getSize() == 2);

    il.addBack(15);
    assert(il.head->data == 5 && il.head->next->data == 10);
    assert(il.tail->data == 15 && il.tail->prev->data == 10);
    assert(il.getSize() == 3);
  }

  // Test for copy constructor to ensure deep copy and independence
  void testCopyConstructor() {
    IntList il;
    il.addBack(1);
    il.addBack(2);
    il.addBack(3);

    IntList copy(il);  // Use copy constructor
    assert(copy.getSize() == 3);
    assert(copy[0] == 1 && copy[1] == 2 && copy[2] == 3);

    // Modify the original list and ensure copy remains unaffected
    il.addBack(4);
    assert(copy.getSize() == 3);  // Copy should be unaffected
    assert(copy[0] == 1 && copy[1] == 2 && copy[2] == 3);
  }

  // Test for assignment operator to ensure deep copy and independence
  void testAssignmentOperator() {
    IntList il;
    il.addBack(1);
    il.addBack(2);
    il.addBack(3);

    IntList assigned;
    assigned = il;  // Use assignment operator
    assert(assigned.getSize() == 3);
    assert(assigned[0] == 1 && assigned[1] == 2 && assigned[2] == 3);

    // Modify the original list and ensure assigned copy remains unaffected
    il.addBack(4);
    assert(assigned.getSize() == 3);  // Assigned copy should be unaffected
    assert(assigned[0] == 1 && assigned[1] == 2 && assigned[2] == 3);
  }

  // Self-assignment test for robustness in assignment operator
  void testSelfAssignment() {
    IntList il;
    il.addBack(1);
    il.addBack(2);

    il = il;  // Self-assignment
    assert(il.getSize() == 2);
    assert(il[0] == 1 && il[1] == 2);
  }

  // Memory integrity test after deleting a copy
  void testDeleteCopy() {
    IntList il;
    il.addBack(1);
    il.addBack(2);
    il.addBack(3);

    IntList * copy = new IntList(il);  // Copy using copy constructor
    delete copy;                       // Delete the copy
    assert(il.getSize() == 3);         // Ensure the original list remains intact
    assert(il[0] == 1 && il[1] == 2 && il[2] == 3);  // Original should be unaffected
  }

  // Test assigning to an empty list
  void testAssignToEmptyList() {
    IntList il;
    il.addBack(1);
    il.addBack(2);
    il.addBack(3);

    IntList emptyList;                 // Create an empty list
    emptyList = il;                    // Assign a populated list to an empty list
    assert(emptyList.getSize() == 3);  // Check assignment was successful
    assert(emptyList[0] == 1 && emptyList[1] == 2 && emptyList[2] == 3);
  }

  // Destructor test to ensure no memory issues
  void testDestructor() {
    IntList * dynamicList = new IntList();
    dynamicList->addBack(1);
    dynamicList->addBack(2);
    dynamicList->addBack(3);

    // Free memory and ensure no memory leaks or crashes
    delete dynamicList;
  }
};

int main() {
  Tester t;
  t.testDefCtor();
  t.testAddFront();
  t.testAddBack();
  t.testCopyConstructor();
  t.testAssignmentOperator();
  t.testSelfAssignment();
  t.testDeleteCopy();
  t.testAssignToEmptyList();
  t.testDestructor();

  std::cout << "All tests passed!" << std::endl;
  return EXIT_SUCCESS;
}
