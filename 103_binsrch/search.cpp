#include <cmath>
#include <cstdio>
#include <cstdlib>

#include "function.h"

int binarySearchForZero(Function<int, int> * f, int low, int high) {
  while (low < high) {
    int mid = (low + high) / 2;  // Implicit floor division for integers
    int result = f->invoke(mid);
    //printf("low:%d, high:%d, mid:%d, result:%d\n", low, high, mid, result);

    if (result == 0) {
      return mid;
    }
    if (result < 0) {
      low = mid + 1;
    }
    else {
      high = mid;
    }
  }
  return (low - 1 >= low) ? (low - 1) : low;
}
