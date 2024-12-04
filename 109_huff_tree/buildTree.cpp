#include "node.h"

Node * buildTree(uint64_t * counts) {
  //WRITE ME!
  priority_queue_t que;

  for (size_t i = 0; i < 257; i++) {
    if (counts[i] > 0) {
      que.push(new Node(i, counts[i]));
    }
  }

  while (que.size() > 1) {
    Node * left = que.top();
    que.pop();
    Node * right = que.top();
    que.pop();
    que.push(new Node(left, right));
  }
  return que.top();
}
