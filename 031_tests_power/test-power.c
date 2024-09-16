#include <stdio.h>
#include <stdlib.h>
unsigned power(unsigned x, unsigned y);

void run_check(unsigned x, unsigned y, unsigned expected_ans) {
  if (x == 0 && y == 0) {
    if (expected_ans != 0) {
      printf("Test failed: power(%u, %u) = %u, expected %u\n", x, y, 0, expected_ans);
      exit(EXIT_FAILURE);
    }
  }
  unsigned result = power(x, y);

  if (result != expected_ans) {
    printf("Test failed: power(%u, %u) = %u, expected %u\n", x, y, result, expected_ans);
    exit(EXIT_FAILURE);
  }
}
int main(void) {
  // Test cases
  run_check(2, 3, 8);  // 2^3 = 8
  run_check(0, 0, 1);
  run_check(1, 100, 1);
  run_check(5, 0, 1);
  run_check(0, 5, 0);

  printf("All tests passed!\n");
  exit(EXIT_SUCCESS);
}
