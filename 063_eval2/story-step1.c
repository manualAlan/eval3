#include <stdio.h>
#include <stdlib.h>

#include "rand_story.h"
int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "wrong number of arguments");
    return EXIT_FAILURE;
  }

  parse_cat(argv[1]);
  return EXIT_SUCCESS;
}
