#include "rand_story.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "provided.h"

void parse_story(char * filename) {
  FILE * f = fopen(filename, "r");
  if (f == NULL) {
    fprintf(stderr, "No file");
    exit(EXIT_FAILURE);
  }

  char * line = NULL;  // copy each line from text
  size_t len = 0;

  while (getline(&line, &len, f) != -1) {  //loop until no lines
    char * pos = line;
    while (*pos != '\0') {
      if (*pos == '_') {
        char * end = strchr(pos + 1, '_');
        if (end == NULL) {
          fprintf(stderr, "Error: unmatched underscore in line.\n");
          free(line);
          fclose(f);
          exit(EXIT_FAILURE);
        }

        // Replace the category between _  with cat
        *end = '\0';  // Temporarily terminate the string at the second underscore
        printf("%s", chooseWord(pos + 1, NULL));  // Call chooseWord with NULL for step 1
        pos = end + 1;
      }
      else {
        putchar(*pos);  // Print non-underscore characters as is
        pos++;
      }
    }
  }

  free(line);
  fclose(f);
}
