#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//This function is used to figure out the ordering of the strings
//in qsort. You do not need to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}
//This function will sort data (whose length is count).
void sortData(char ** data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);
}
void processInput(FILE * f) {
  char * line = NULL;
  size_t sz = 0;
  char ** lines = NULL;
  size_t count = 0;
  while (getline(&line, &sz, f) >= 0) {
    lines = realloc(lines, (count + 1) * sizeof(*lines));
    lines[count] = line;
    count++;
    line = NULL;
  }
  free(line);
  sortData(lines, count);
  for (size_t i = 0; i < count; i++) {
    printf("%s", lines[i]);
    free(lines[i]);
  }
  free(lines);
}
int main(int argc, char ** argv) {
  //WRITE YOUR CODE HERE!
  if (argc == 1) {
    processInput(stdin);
  }
  else {
    for (int i = 1; i < argc; i++) {
      FILE * f = fopen(argv[i], "r");
      if (f == NULL) {
        perror("Could not open file");
        return EXIT_FAILURE;
      }
      processInput(f);
      if (fclose(f) != 0) {
        perror("Failed to close file");
        return EXIT_FAILURE;
      }
    }
  }
  return EXIT_SUCCESS;
}
