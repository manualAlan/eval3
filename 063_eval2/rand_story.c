#include "rand_story.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "provided.h"

// Geneeral function to add a word to a dynamically allocated list
void addWordToList(char *** list, size_t * n_words, const char * word) {
  *list = realloc(*list, (*n_words + 1) * sizeof(**list));
  if (*list == NULL) {
    fprintf(stderr, "Error: memory allocation failed\n");
    exit(EXIT_FAILURE);
  }
  (*list)[*n_words] = strdup(word);
  (*n_words)++;
}

// Find or create a category in a given catArray, return this category's address
category_t * findOrCreateCategory(catarray_t * cats, const char * name) {
  for (size_t i = 0; i < cats->n; i++) {  // if already exist, give teh address
    if (strcmp(cats->arr[i].name, name) == 0) {
      return &cats->arr[i];
    }
  }  //else realloc the array to 1 larger and put category into it
  cats->arr = realloc(cats->arr, (cats->n + 1) * sizeof(*cats->arr));
  if (cats->arr == NULL) {
    fprintf(stderr, "Memory allocation fail \n");
    exit(EXIT_FAILURE);
  }
  category_t * newCat = &cats->arr[cats->n];
  newCat->name = strdup(name);
  newCat->words = NULL;
  newCat->n_words = 0;
  cats->n++;
  return newCat;
}

// Parse the words file and return a catarray with these
catarray_t * parseWords(const char * filename) {
  FILE * f = fopen(filename, "r");
  if (f == NULL) {
    fprintf(stderr, "could not open file %s\n", filename);
    exit(EXIT_FAILURE);
  }
  // Allocate memory for the catarray
  catarray_t * cats = malloc(sizeof(*cats));
  if (cats == NULL) {
    fprintf(stderr, "Memory allocation failure\n");
    fclose(f);
    exit(EXIT_FAILURE);
  }
  cats->arr = NULL;
  cats->n = 0;
  // Read the file line by line
  char * line = NULL;
  size_t len = 0;
  // Look for the colon separator in between
  while (getline(&line, &len, f) >= 0) {
    char * colon = strchr(line, ':');
    if (colon == NULL) {
      fprintf(stderr, "Wrong format in line: %s\n", line);
      free(line);
      fclose(f);
      exit(EXIT_FAILURE);
    }
    *colon = '\0';
    char * categoryName = line;
    char * word = colon + 1;
    word[strcspn(word, "\n")] = '\0';

    category_t * cat = findOrCreateCategory(cats, categoryName);
    addWordToList(&cat->words, &cat->n_words, word);
  }
  //free memory and close file
  free(line);
  fclose(f);
  return cats;
}

//a freecatarray function that frees elements from bottom up
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

//typedef struct usedWords_tag usedWords;
// Parse the story temp and print with swaped words
void parseAndPrint(const char * filename, catarray_t * cats) {
  FILE * f = fopen(filename, "r");
  if (f == NULL) {
    fprintf(stderr, "Cannot open file %s\n", filename);
    exit(EXIT_FAILURE);
  }
  size_t len = 0;

  char * line = NULL;
  // track previously used words
  usedWords usedWordsList = {NULL, 0};

  // Read the file line by line and locate words with__
  while (getline(&line, &len, f) >= 0) {
    char * pos = line;
    while (*pos != '\0') {
      if (*pos == '_') {
        char * end = strchr(pos + 1, '_');
        if (end == NULL) {
          fprintf(stderr, "Error unmatched underscore in line\n");
          free(line);
          fclose(f);
          exit(EXIT_FAILURE);
        }

        *end = '\0';
        char * category = pos + 1;
        // Check if the placeholder is a reference to a previous word
        if (isdigit(category[0])) {
          size_t refIndex = strtoul(category, NULL, 10);
          const char * previousWord = getPreviousWord(&usedWordsList, refIndex);
          printf("%s", previousWord);
          addWordToList(&usedWordsList.usedWords, &usedWordsList.n_used, previousWord);
        }
        else {  //if not, treat it as a category name and choose random word
          const char * chosenWord = chooseWord(category, cats);
          printf("%s", chosenWord);
          addWordToList(&usedWordsList.usedWords, &usedWordsList.n_used, chosenWord);
        }

        pos = end + 1;
      }
      else {
        putchar(*pos);
        pos++;
      }
    }
  }

  for (size_t i = 0; i < usedWordsList.n_used; i++) {
    free(usedWordsList.usedWords[i]);
  }
  free(usedWordsList.usedWords);

  free(line);
  fclose(f);
}

// Retrieve a previously used word based on an index
const char * getPreviousWord(usedWords * usedWordsList, size_t index) {
  if (index == 0 || index > usedWordsList->n_used) {
    fprintf(stderr, "Error. Invalid reference\n");
    exit(EXIT_FAILURE);
  }
  return usedWordsList->usedWords[usedWordsList->n_used - index];
}
