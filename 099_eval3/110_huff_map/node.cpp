#include "node.h"
void Node::buildMap(BitString b, std::map<unsigned, BitString> & theMap) {
  //WRITE ME!
  if (sym != NO_SYM) {
    assert(left == right && left == NULL);
    theMap[sym] = b;
    return;
  }
  assert(left != NULL);
  assert(right != NULL);
  left->buildMap(b.plusZero(), theMap);

  right->buildMap(b.plusOne(), theMap);
  return;
}
