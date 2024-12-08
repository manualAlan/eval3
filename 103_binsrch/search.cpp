#include <cmath>
#include <cstdio>
#include <cstdlib>

#include "function.h"

int binarySearchForZero(Function<int, int> * f, int low, int high) {
  int start = low;
  int end = high;
  while (start < end) {
    int middle = floor((start + end) / 2.0);
    int value = f->invoke(middle);
    //printf("start:%d, end:%d, middle:%d, value:%d\n", start, end, middle, value);

    if (value == 0) {
      return middle;
    }
    else if (value < 0) {
      start = middle + 1;
    }
    else {
      end = middle;
    }
  }
  return (start - 1 < low) ? start : start - 1;
}
