#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "counts.h"
#include "kv.h"
#include "outname.h"

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  //WRITE ME
  FILE * f = fopen(filename, "r");
  if (f == NULL) {
    perror("Could not open file");
    return NULL;
  }

  counts_t * counts = createCounts();
  if (counts == NULL) {
    fclose(f);
    return NULL;
  }

  char * line = NULL;
  size_t sz = 0;
  while (getline(&line, &sz, f) >= 0) {
    line[strcspn(line, "\n")] = '\0';  // Remove newline character
    char * value = lookupValue(kvPairs, line);
    addCount(counts, value);
  }

  free(line);
  fclose(f);
  return counts;
}

int main(int argc, char ** argv) {
  if (argc < 3) {
    fprintf(stderr, "Usage: %s <kv_file> <list_file1> ... <list_fileN>\n", argv[0]);
    return EXIT_FAILURE;
  }

  kvarray_t * kv = readKVs(argv[1]);
  if (kv == NULL) {
    return EXIT_FAILURE;
  }

  for (int i = 2; i < argc; i++) {
    counts_t * counts = countFile(argv[i], kv);
    if (counts == NULL) {
      freeKVs(kv);
      return EXIT_FAILURE;
    }

    char * outName = computeOutputFileName(argv[i]);
    if (outName == NULL) {
      freeCounts(counts);
      freeKVs(kv);
      return EXIT_FAILURE;
    }

    FILE * f = fopen(outName, "w");
    if (f == NULL) {
      perror("Could not open output file");
      free(outName);
      freeCounts(counts);
      freeKVs(kv);
      return EXIT_FAILURE;
    }

    printCounts(counts, f);
    fclose(f);

    free(outName);
    freeCounts(counts);
  }

  freeKVs(kv);
  return EXIT_SUCCESS;
  //WRITE ME (plus add appropriate error checking!)
  //read the key/value pairs from the file named by argv[1] (call the result kv)

  //count from 2 to argc (call the number you count i)

  //count the values that appear in the file named by argv[i], using kv as the key/value pair
  //   (call this result c)

  //compute the output file name from argv[i] (call this outName)

  //open the file named by outName (call that f)

  //print the counts from c into the FILE f

  //close f

  //free the memory for outName and c

  //free the memory for kv

  return EXIT_SUCCESS;
}
