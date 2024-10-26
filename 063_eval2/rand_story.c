#include "rand_story.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "provided.h"

//General function to add a word to a dynamically allocated list
void addWordToList(char *** list, size_t * n_words, const char * word) {
  *list = realloc(*list, (*n_words + 1) * sizeof(**list));
  if (*list == NULL) {
    fprintf(stderr, " memory allocation failed\n");
    exit(EXIT_FAILURE);
  }
  (*list)[*n_words] = strdup(word);
  (*n_words)++;
}

//Find or create a category in a given catArray, return this category's address
category_t * findOrCreateCategory(catarray_t * cats, const char * name) {
  for (size_t i = 0; i < cats->n; i++) {  // if already exist, give the address
    if (strcmp(cats->arr[i].name, name) == 0) {
      return &cats->arr[i];
    }
  }  // else realloc the array to 1 larger and put category into it
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

//parse the words file and return a catarray with these
catarray_t * parseWords(const char * filename) {
  FILE * f = fopen(filename, "r");
  if (f == NULL) {
    fprintf(stderr, "could not open file %s\n", filename);
    exit(EXIT_FAILURE);
  }
  //allocate memory for the catarray
  catarray_t * cats = malloc(sizeof(*cats));
  if (cats == NULL) {
    fprintf(stderr, "Memory allocation failure\n");
    fclose(f);
    exit(EXIT_FAILURE);
  }
  cats->arr = NULL;
  cats->n = 0;
  //read the file line by line
  char * line = NULL;
  size_t len = 0;
  //look for the colon separator in between
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
  // free memory and close file
  free(line);
  fclose(f);
  return cats;
}

// a freeCatArray function that frees elements from bottom up
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

//   typedef struct usedWords_tag usedWords;
//Parse the story template and print with swapped words
void parseAndPrint(const char * filename, catarray_t * cats, int noReuse) {
  FILE * f = fopen(filename, "r");
  if (f == NULL) {
    fprintf(stderr, "Cannot open file %s\n", filename);
    exit(EXIT_FAILURE);
  }

  size_t len = 0;
  char * line = NULL;
  usedWords usedWordsList = {NULL, 0};  //rack previously used words

  //read the file line by line
  while (getline(&line, &len, f) >= 0) {
    char * pos = line;  //Start of the current line
    while (*pos != '\0') {
      if (*pos == '_') {
        char * end = strchr(pos + 1, '_');  //Find the closing _
        if (end == NULL) {
          fprintf(stderr, "Error: unmatched underscore in line\n");
          free(line);
          fclose(f);
          exit(EXIT_FAILURE);
        }

        *end = '\0';
        //Temporarily terminate the string at the closing underscore
        char * category = pos + 1;

        // Handle back-references to previous words
        if (isdigit(category[0])) {
          size_t i = strtoul(category, NULL, 10);
          const char * previousWord = getPreviousWord(&usedWordsList, i);
          printf("%s", previousWord);
          addWordToList(&usedWordsList.usedWords,
                        &usedWordsList.n_used,
                        previousWord);  // Add to used words list
        }
        else {
          const char * chosenWord = NULL;

          if (noReuse) {
            int attempts = 0;
            const int max_attempts = 1000;
            // check no resue case
            do {
              chosenWord = chooseWord(category, cats);
              if (chosenWord == NULL || attempts > max_attempts) {
                fprintf(stderr, "No available words left in '%s'\n", category);
                exit(EXIT_FAILURE);
                attempts++;
              }
            } while (wordAlreadyUsed(&usedWordsList,
                                     chosenWord));  //Ensure word is not reused
          }
          else {
            chosenWord = chooseWord(category, cats);
            //chosenWord = chooseWord(category, cats);
            if (chosenWord == NULL) {
              fprintf(stderr, "Error: No words available for category '%s'\n", category);
              exit(EXIT_FAILURE);
            }
          }

          printf("%s", chosenWord);
          if (noReuse) {
            removeUsedWord(cats, category, chosenWord);
          }
          addWordToList(&usedWordsList.usedWords,
                        &usedWordsList.n_used,
                        chosenWord);  //dd to used words list
        }

        pos = end + 1;  //move past the closing underscore
      }
      else {
        putchar(*pos);  // Print non-placeholder characters
        pos++;
      }
    }
  }

  //free the usedWords list
  for (size_t i = 0; i < usedWordsList.n_used; i++) {
    free(usedWordsList.usedWords[i]);
  }
  free(usedWordsList.usedWords);
  free(line);
  fclose(f);
}
int wordAlreadyUsed(usedWords * usedWordsList, const char * word) {
  for (size_t i = 0; i < usedWordsList->n_used; i++) {
    if (strcmp(usedWordsList->usedWords[i], word) == 0) {
      return 1;  // Word has already been used
    }
  }
  return 0;  // Word has not been used
}

void removeUsedWord(catarray_t * cats, const char * category, const char * word) {
  for (size_t i = 0; i < cats->n; i++) {
    if (strcmp(cats->arr[i].name, category) == 0) {
      for (size_t j = 0; j < cats->arr[i].n_words; j++) {
        if (strcmp(cats->arr[i].words[j], word) == 0) {
          //   move the last word to the current position And reduce
          //          free(cats->arr[i].words[j]);
          //cats->arr[i].words[j] = NULL;
          free(cats->arr[i].words[j]);
          cats->arr[i].words[j] = cats->arr[i].words[cats->arr[i].n_words - 1];
          cats->arr[i].words[cats->arr[i].n_words - 1] = NULL;
          cats->arr[i].n_words--;
          return;
        }
      }
    }
  }
}

//Retrieve a previously used word based on an index
const char * getPreviousWord(usedWords * usedWordsList, size_t index) {
  if (index == 0 || index > usedWordsList->n_used) {
    fprintf(stderr, "Error. Invalid reference\n");
    exit(EXIT_FAILURE);
  }
  return usedWordsList->usedWords[usedWordsList->n_used - index];
}
