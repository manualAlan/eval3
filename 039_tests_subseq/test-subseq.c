#include <stdio.h>
#include <stdlib.h>

// Declare the maxSeq function (defined in object file)
size_t maxSeq(int * array, size_t n);

void test_maxSeq() {
  // Test 1: Empty array
  int arr1[] = {};
  if (maxSeq(arr1, 0) != 0) {
    printf("Test 1 (empty array) failed\n");
    exit(EXIT_FAILURE);
  }

  // Test 2: Single element array
  int arr2[] = {5};
  if (maxSeq(arr2, 1) != 1) {
    printf("Test 2 (single element array) failed\n");
    exit(EXIT_FAILURE);
  }

  // Test 3: All elements the same
  int arr3[] = {3, 3, 3, 3};
  if (maxSeq(arr3, 4) != 1) {
    printf("Test 3 (all same elements) failed\n");
    exit(EXIT_FAILURE);
  }

  // Test 4: Strictly increasing array
  int arr4[] = {1, 2, 3, 4, 5};
  if (maxSeq(arr4, 5) != 5) {
    printf("Test 4 (strictly increasing) failed\n");
    exit(EXIT_FAILURE);
  }

  // Test 5: Strictly decreasing array
  int arr5[] = {5, 4, 3, 2, 1};
  if (maxSeq(arr5, 5) != 1) {
    printf("Test 5 (strictly decreasing) failed\n");
    exit(EXIT_FAILURE);
  }

  // Test 6: Mixed array
  int arr6[] = {10, 5, 7, 1, 6, 8, 2, 9};
  if (maxSeq(arr6, 8) != 3) {  // max increasing sequence is {1, 6, 8}
    printf("Test 6 (mixed array) failed\n");
    exit(EXIT_FAILURE);
  }
  int arr7[] = {1, 2, 2, 3, 4};
  if (maxSeq(arr7, 5) != 3) {  // max increasing subsequence is {2, 3, 4}
    printf("Test 7 (array with repeated elements) failed\n");
    exit(EXIT_FAILURE);
  }

  // Test 8: Two large subsequences
  int arr8[] = {1, 2, 3, 1, 4, 5, 6};
  if (maxSeq(arr8, 7) != 4) {  // max increasing subsequence is {1, 4, 5, 6}
    printf("Test 8 (two large subsequences) failed\n");
    exit(EXIT_FAILURE);
  }
  int arr9[] = {1, 2, 3, 2, 3, 4};
  if (maxSeq(arr9, 6) != 3) {
    printf('failure');
    exit(EXIT_FAILURE);
  }
  printf("All tests passed!\n");
}

int main() {
  test_maxSeq();
  return EXIT_SUCCESS;
}
