#include "rand_story.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "provided.h"

void parse_cat(char * filename) {
  FILE * f = fopen(filename, "r");
  if (f == NULL) {
    fprintf(stderr, "No file");
    exit(EXIT_FAILURE);
  }

  char * line = NULL;  // copy each line from text
  size_t len = 0;

  while (getline(&line, &len, f) >= 0) {  //loop until no lines
    char * pos = line;
    while (*pos != '\0') {
      if (*pos == '_') {
        char * end = strchr(pos + 1, '_');  // check if end in _
        if (end == NULL) {
          fprintf(stderr, "No ending _ in line.\n");
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
        putchar(*pos);  // Print non-_  character
        pos++;
      }
    }
  }

  free(line);
  fclose(f);
}
category_t * findOrCreateCategory(catarray_t * cats, const char * name) {
  for (size_t i = 0; i < cats->n; i++) {
    if (strcmp(cats->arr[i].name, name) == 0) {
      return &cats->arr[i];
    }
  }
  cats->arr = realloc(cats->arr, (cats->n + 1) * sizeof(*cats->arr));
  if (cats->arr == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    exit(EXIT_FAILURE);
  }
  category_t * newCat = &cats->arr[cats->n];
  newCat->name = strdup(name);
  newCat->words = NULL;
  newCat->n_words = 0;
  cats->n++;
  return newCat;
}

void addWordToCategory(category_t * cat, const char * word) {
  cat->words = realloc(cat->words, (cat->n_words + 1) * sizeof(*cat->words));
  if (cat->words == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    exit(EXIT_FAILURE);
  }
  cat->words[cat->n_words] = strdup(word);
  cat->n_words++;
}

catarray_t * parseWords(const char * filename) {
  FILE * f = fopen(filename, "r");
  if (f == NULL) {
    perror("Could not open file");
    exit(EXIT_FAILURE);
  }

  catarray_t * cats = malloc(sizeof(*cats));
  if (cats == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    fclose(f);
    exit(EXIT_FAILURE);
  }
  cats->arr = NULL;
  cats->n = 0;

  char * line = NULL;
  size_t len = 0;
  while (getline(&line, &len, f) != -1) {
    char * colon = strchr(line, ':');
    if (colon == NULL) {
      fprintf(stderr, "Error: Invalid format in line: %s\n", line);
      free(line);
      fclose(f);
      exit(EXIT_FAILURE);
    }
    *colon = '\0';
    char * categoryName = line;
    char * word = colon + 1;
    word[strcspn(word, "\n")] = '\0';

    category_t * cat = findOrCreateCategory(cats, categoryName);
    addWordToCategory(cat, word);
  }

  free(line);
  fclose(f);
  return cats;
}

void freeCatArray(catarray_t * cats) {
  for (size_t i = 0; i < cats->n; i++) {
    for (size_t j = 0; j < cats->arr[i].n_words; j++) {
      free(cats->arr[i].words[j]);
    }
    free(cats->arr[i].words);
    free(cats->arr[i].name);
  }
  free(cats->arr);
  free(cats);
}
