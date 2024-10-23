#include <stdio.h>
#include <stdlib.h>

#include "rand_story.h"
int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "wrong number of arguments", argv[0]);
    return EXIT_FAILURE;
  }

  parse_story(argv[1]);

  return EXIT_SUCCESS;
}
