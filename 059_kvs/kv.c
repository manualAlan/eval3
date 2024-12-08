#include "kv.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char * extractKey(const char * line) {
  char * eq_pos = strchr(line, '=');
  size_t key_len = eq_pos - line;
  char * key = malloc(key_len + 1);
  strncpy(key, line, key_len);
  key[key_len] = '\0';
  return key;
}

static char * extractValue(const char * line) {
  char * eq_pos = strchr(line, '=');
  char * value = strdup(eq_pos + 1);
  value[strcspn(value, "\n")] = '\0';  // Remove newline character
  return value;
}

kvarray_t * readKVs(const char * fname) {
  FILE * f = fopen(fname, "r");
  if (f == NULL) {
    perror("Could not open file");
    return NULL;
  }

  kvarray_t * kv_array = malloc(sizeof(*kv_array));
  kv_array->pairs = NULL;
  kv_array->length = 0;

  char * line = NULL;
  size_t sz = 0;
  while (getline(&line, &sz, f) >= 0) {
    kv_array->pairs =
        realloc(kv_array->pairs, (kv_array->length + 1) * sizeof(*(kv_array->pairs)));
    kv_array->pairs[kv_array->length].key = extractKey(line);
    kv_array->pairs[kv_array->length].value = extractValue(line);
    kv_array->length++;
  }
  free(line);
  fclose(f);
  return kv_array;
}

void freeKVs(kvarray_t * pairs) {
  for (size_t i = 0; i < pairs->length; i++) {
    free(pairs->pairs[i].key);
    free(pairs->pairs[i].value);
  }
  free(pairs->pairs);
  free(pairs);
}

void printKVs(kvarray_t * pairs) {
  for (size_t i = 0; i < pairs->length; i++) {
    printf("key = '%s' value = '%s'\n", pairs->pairs[i].key, pairs->pairs[i].value);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  for (size_t i = 0; i < pairs->length; i++) {
    if (strcmp(pairs->pairs[i].key, key) == 0) {
      return pairs->pairs[i].value;
    }
  }
  return NULL;
}
