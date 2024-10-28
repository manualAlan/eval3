#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rand_story.h"

int main(int argc, char ** argv) {
  int noReuse = 0;

  // Check for the -n flag
  if (argc == 4 && strcmp(argv[1], "-n") == 0) {
    noReuse = 1;
  }
  else if (argc != 3) {
    fprintf(stderr, "wrong # of arg");
    return EXIT_FAILURE;
  }
  const char * wordFile;
  const char * storyFile;

  if (noReuse) {
    wordFile = argv[2];
    storyFile = argv[3];
  }
  else {
    wordFile = argv[1];
    storyFile = argv[2];
  }

  catarray_t * cats = parseWords(wordFile);

  parseAndPrint(storyFile, cats, noReuse);

  //free the memory used by the category array
  freeCatArray(cats);
  return EXIT_SUCCESS;
}
