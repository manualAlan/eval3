#include "counts.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
counts_t * createCounts(void) {
  counts_t * c = malloc(sizeof(*c));
  if (c == NULL) {
    return NULL;
  }
  c->counts = NULL;
  c->size = 0;
  c->unknown_count = 0;
  return c;  //WRITE ME
}
void addCount(counts_t * c, const char * name) {
  //WRITE ME
  if (name == NULL) {
    c->unknown_count++;
    return;
  }
  for (size_t i = 0; i < c->size; i++) {
    if (strcmp(c->counts[i].name, name) == 0) {
      c->counts[i].count++;
      return;
    }
  }
  c->counts = realloc(c->counts, (c->size + 1) * sizeof(*c->counts));
  c->counts[c->size].name = strdup(name);
  c->counts[c->size].count = 1;
  c->size++;
}
void printCounts(counts_t * c, FILE * outFile) {
  //WRITE ME
  for (size_t i = 0; i < c->size; i++) {
    fprintf(outFile, "%s: %d\n", c->counts[i].name, c->counts[i].count);
  }
  if (c->unknown_count > 0) {
    fprintf(outFile, "<unknown> : %d\n", c->unknown_count);
  }
}

void freeCounts(counts_t * c) {
  for (size_t i = 0; i < c->size; i++) {
    free(c->counts[i].name);
  }
  free(c->counts);
  free(c);
  //WRITE ME
}
