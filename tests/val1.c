#include <stdlib.h>

int main(void) {
  size_t n = 4;
  int * x = malloc(sizeof(n));  // Allocates memory
  for (size_t i = 0; i < n; i++) {
    x[i] = i;  // Writes to allocated memory
  }
  free(x);  // Frees the allocated memory
  return EXIT_SUCCESS;
}
