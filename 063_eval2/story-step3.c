#include <stdio.h>
#include <stdlib.h>

#include "provided.h"
#include "rand_story.h"

int main(int argc, char ** argv) {
  if (argc != 3) {
    fprintf(stderr, "wrong number of arguments");
    return EXIT_FAILURE;
  }

  catarray_t * cats = parseWords(argv[1]);
  parseAndPrint(argv[2], cats);
  freeCatArray(cats);

  return EXIT_SUCCESS;
}
