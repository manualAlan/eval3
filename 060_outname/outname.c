#include "outname.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * computeOutputFileName(const char * inputName) {
  const char * suffix = ".counts";
  size_t inputLen = strlen(inputName);
  size_t suffixLen = strlen(suffix);

  char * outputName = malloc(inputLen + suffixLen + 1);
  if (outputName == NULL) {
    perror("Failed to allocate memory");
    return NULL;
  }

  strcpy(outputName, inputName);
  strcat(outputName, suffix);

  return outputName;
  //WRITE ME
}
