#include <stdio.h>
#include <stdlib.h>

#include "provided.h"
#include "rand_story.h"

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <word file>\n", argv[0]);
    return EXIT_FAILURE;
  }

  catarray_t * categories = parseWords(argv[1]);
  printWords(categories);
  freeCatArray(categories);

  return EXIT_SUCCESS;
}
