#include <stdio.h>
#include <stdlib.h>
unsigned power(unsigned x, unsigned y);

void run_check(unsigned x, unsigned y, unsigned expected_ans) {
  unsigned result = power(x, y);

  if (result != expected_ans) {
    printf("Test failed: power(%u, %u) = %u, expected %u\n", x, y, result, expected_ans);
    exit(EXIT_FAILURE);
  }
}
int main(void) {
  // Test cases
  run_check(2, 3, 8);
  run_check(0, 0, 1);
  run_check(1, 100, 1);
  run_check(5, 0, 1);
  run_check(0, 5, 0);
  run_check(3, 4, 81);
  run_check(2, 31, 2147483648);          // 2^31 = 2147483648
  run_check(999, 2, 998001);             // 999^2 = 998001
  run_check(1000, 3, 1000000000);        // 1000^3 = 1000000000
  run_check(1, 1000, 1);                 // 1^1000 = 1
  run_check(2, 16, 65536);               // 2^16 = 65536
  run_check(4294967295, 1, 4294967295);  // UINT_MAX^1 = UINT_MAX
  run_check(65535, 2, 4294836225);       // 65535^2 = 4294836225

  printf("All tests passed!\n");
  exit(EXIT_SUCCESS);
}
