#include <assert.h>

#include <cstdlib>
#include <iostream>

#include "il.hpp"

class Tester {
 private:
  void checkStruct(IntList & il) {
    int size = il.getSize();
    if (size == 0) {
      assert(il.head == NULL);
      assert(il.tail == NULL);
      return;
    }
    if (size <= 1) {
      assert(il.head == il.tail);
    }
    else {
      assert(il.head != il.tail);
    }

    assert(il.tail != NULL);
    IntList::Node * node = il.head;
    for (int i = 0; i < size; i++) {
      assert(node->data == il[i]);
      if (i < size - 1) {
        assert(node->next->data == il[i + 1]);
        assert(node->next->prev == node);
      }
      else {
        assert(node == il.tail);
        assert(node->next == NULL);
      }
      if (i > 0) {
        assert(node->prev->data == il[i - 1]);
        assert(node->prev->next == node);
      }
      else {
        assert(node == il.head);
        assert(node->prev == NULL);
      }
      node = node->next;
    }
    assert(node == NULL);
    return;
  }

 public:
  // testing for default constructor is done for you
  void testDefCtor() {
    IntList il;
    assert(il.head == NULL);
    assert(il.tail == NULL);
    assert(il.getSize() == 0);
  }
  // example of another method you might want to write
  void testAddFront() {
    // WRITE ME
    IntList il;
    il.addFront(0);
    assert(il.getSize() == 1);
    assert(il[0] == 0);
    checkStruct(il);
    il.addFront(2);
    assert(il.getSize() == 2);
    assert(il[0] == 2);
    assert(il[1] == 0);
    checkStruct(il);
  }
  // many more tester methods
  void testAddBack() {
    IntList il;
    checkStruct(il);
    il.addBack(1);
    assert(il.getSize() == 1);
    assert(il[0] == 1);
    checkStruct(il);
    il.addBack(2);
    assert(il.getSize() == 2);
    assert(il[0] == 1);
    assert(il[1] == 2);
    checkStruct(il);
    il[1] = 10;
    assert(il[1] == 10);
    checkStruct(il);
    il.addBack(3);
    assert(il.getSize() == 3);
    assert(il[2] == 3);
    checkStruct(il);
  }
  void testCopy() {
    IntList il1;
    il1.addBack(1);
    il1.addBack(2);
    il1[1] = 3;
    IntList il2(il1);
    assert(il2.getSize() == 2);
    assert(il2[0] == 1);
    assert(il2[1] == 3);
    checkStruct(il2);
    IntList il3 = il2;
    assert(il3.getSize() == 2);
    assert(il3[0] == 1);
    assert(il3[1] == 3);
    checkStruct(il3);
    IntList il4;
    il4 = il1;
    assert(il4[0] == 1);
    assert(il4[1] == 3);
    assert(il4.getSize() == 2);
    checkStruct(il4);
    il4 = il3;
    assert(il4.getSize() == 2);
    assert(il4[0] == 1);
    assert(il4[1] == 3);
    checkStruct(il4);
  }
  void testRemove() {
    IntList il;
    il.addBack(1);
    il.addBack(2);
    il.remove(il[0]);
    assert(il.getSize() == 1);
    checkStruct(il);
    assert(il[0] == 2);
    il.remove(il[0]);
    assert(il.getSize() == 0);
    checkStruct(il);
    il.addBack(1);
    il.addFront(0);
    il.addFront(-1);
    assert(il[0] == -1);
    assert(il[1] == 0);
    assert(il[2] == 1);
    assert(il.getSize() == 3);
    checkStruct(il);
    assert(il.remove(0) == true);
    assert(il[0] == -1);
    assert(il[1] == 1);
    assert(il.getSize() == 2);
    checkStruct(il);
    assert(il.remove(888) == false);
    assert(il.getSize() == 2);
    checkStruct(il);
    assert(il.remove(1) == true);
    assert(il.getSize() == 1);
    checkStruct(il);
  }
};

int main(void) {
  Tester t;
  t.testDefCtor();
  t.testAddFront();
  t.testAddBack();
  t.testCopy();
  t.testRemove();
  // write calls to your other test methods here
  return EXIT_SUCCESS;
}
