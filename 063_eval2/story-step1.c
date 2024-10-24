#include <stdio.h>
#include <stdlib.h>

#include "rand_story.h"
int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "wrong number of arguments");
    return EXIT_FAILURE;
  }

  //parseAndPrint(argv[1], NULL);
  //pa
  parseAndPrint(argv[1], NULL, 0);
  return EXIT_SUCCESS;
}
