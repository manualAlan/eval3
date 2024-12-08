//final final
#include "rand_story.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "provided.h"
//helper function
void printCatArray(const catarray_t * catarray) {
  if (catarray == NULL) {
    fprintf(stderr, "Catarray is NULL.\n");
    return;
  }

  //Print the total number of categories
  printf("Number of categories: %zu\n\n", catarray->n);

  //loop through each category and print its details
  for (size_t i = 0; i < catarray->n; i++) {
    category_t * category = &catarray->arr[i];
    printf("Category: %s\n", category->name);
    printf("Number of words: %zu\n", category->n_words);
    printf("Words:\n");

    // Print each word in the category
    for (size_t j = 0; j < category->n_words; j++) {
      printf("  %s\n", category->words[j]);
    }

    printf("\n");
  }
}

//General function to add a word to a dynamically allocated list
void addWordToList(char *** list, size_t * n_words, const char * word) {
  *list = realloc(*list, (*n_words + 1) * sizeof(**list));
  if (*list == NULL) {
    fprintf(stderr, " memory allocation failed\n");
    exit(EXIT_FAILURE);
  }
  (*list)[*n_words] = strdup(word);
  (*n_words)++;
  //X  fprintf(stderr, "Allocated memory for word: %s\n", word);
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
/*
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
*/
void freeCatArray(catarray_t * cats) {
  if (cats == NULL) {
    return;
  }
  for (size_t i = 0; i < cats->n; i++) {
    if (cats->arr[i].words != NULL) {
      for (size_t j = 0; j < cats->arr[i].n_words; j++) {
        free(cats->arr[i].words[j]);  //free each word
      }
      free(cats->arr[i].words);  //Free the array of word pointers
    }
    free(cats->arr[i].name);  //free category name
  }
  free(cats->arr);  // free the array of category structures
  free(cats);       //free the catarray_t structure itself
}

//hwlper function checking if category exists in cats
int categoryExists(catarray_t * cats, const char * category) {
  for (size_t i = 0; i < cats->n; i++) {
    if (strcmp(cats->arr[i].name, category) == 0) {
      return 1;  //exsit
    }
  }
  return 0;  //does not exist
}
//   typedef struct usedWords_tag usedWords;
//Parse the story template and print with swapped words
//helper function to open a file and handle errors
FILE * openFile(const char * filename) {
  FILE * f = fopen(filename, "r");
  if (f == NULL) {
    fprintf(stderr, "Cannot open file %s\n", filename);
    exit(EXIT_FAILURE);
  }
  return f;
}

//helper function to free the usedWords list
void freeUsedWords(usedWords * usedWordsList) {
  for (size_t i = 0; i < usedWordsList->n_used; i++) {
    free(usedWordsList->usedWords[i]);
  }
  free(usedWordsList->usedWords);
}

//helper function to handle back-references eg _1_
const char * handleBackReference(const char * category, usedWords * usedWordsList) {
  char * endPtr;
  long int index = strtol(category, &endPtr, 10);
  if (*endPtr == '\0' && index > 0 && index <= usedWordsList->n_used) {
    return getPreviousWord(usedWordsList, (size_t)index);
  }
  fprintf(stderr, "Error: Invalid back-reference '%s'\n", category);
  return NULL;
}
/*
//helper function to choose a word from a category, considering noReuse
const char * chooseCategoryWord(const char * category,
                                catarray_t * cats,
                                 usedWords * usedWordsList,
                                int noReuse) {
  const char * chosenWord = NULL;
  if (noReuse) {
    int attempts = 0;
    const int max_attempts = 1000;
    while (attempts < max_attempts) {
      // Cast category to char * to match the chooseWord function's parameter type
      chosenWord = chooseWord((char *)category, cats);
      if (chosenWord == NULL) {
        fprintf(stderr, "No available words left in '%s'\n", category);
        return NULL;
      }
      attempts++;
    }  // while (wordAlreadyUsed(usedWordsList, chosenWord));
    fprintf(stderr, "No available words left in '%s'\n", category);
    return NULL;
  }
  else {
    // Cast category to char * to match the chooseWord function's parameter type
    chosenWord = chooseWord((char *)category, cats);
    if (chosenWord == NULL) {
      fprintf(stderr, "Error: No words available for category '%s'\n", category);
    }
  }
  return chosenWord;
}
*/
// Helper function to process each line, performing substitutions exactly as the original logic
void processLine(char * line, catarray_t * cats, int noReuse, usedWords * usedWordsList) {
  char * pos = line;  // Start of the current line
  while (*pos != '\0') {
    if (*pos == '_') {
      char * end = strchr(pos + 1, '_');  // Find the closing underscore
      if (end == NULL) {
        fprintf(stderr, "Error: unmatched underscore in line\n");
        exit(EXIT_FAILURE);
      }
      *end = '\0';
      //temporarily terminate the string at the closing underscore
      char * category = pos + 1;
      const char * chosenWord = NULL;
      char * endPtr;
      int index = strtol(category, &endPtr, 10);

      if (!(cats == NULL) && *endPtr == '\0' &&
          index > 0) {  //check if the category is a valid integer
        if (index > usedWordsList->n_used) {
          fprintf(stderr, "Error: Invalid back-reference '%s'\n", category);
          exit(EXIT_FAILURE);
        }
        //get the previously used word
        chosenWord = getPreviousWord(usedWordsList, (size_t)index);
      }
      else if (!(cats == NULL) && !categoryExists(cats, category)) {
        //     Exit failure for non-integer categories that don't exist
        fprintf(stderr, "Category '%s' does not exist\n", category);
        exit(EXIT_FAILURE);
      }
      else {
        //category exists, proceed to choose a word
        if (noReuse) {
          // int attempts = 0;
          // const int max_attempts = 1000;
          // for (int attempts = 0; attempts < max_attempts; attempts++) {
          chosenWord = chooseWord(category, cats);
          if (chosenWord == NULL) {
            fprintf(stderr, "No available words left in '%s'\n", category);
            exit(EXIT_FAILURE);
          }
          //exit(EXIT_FAILURE);
        }
        else {
          chosenWord = chooseWord(category, cats);
          if (chosenWord == NULL) {
            fprintf(stderr, "Error: No words available for category '%s'\n", category);
            exit(EXIT_FAILURE);
          }
        }
      }
      //print the chosen word if was found
      if (chosenWord != NULL) {
        printf("%s", chosenWord);
        addWordToList(&usedWordsList->usedWords, &usedWordsList->n_used, chosenWord);
        if (noReuse) {
          removeUsedWord(cats, category, chosenWord);
        }
      }
      pos = end + 1;  //move past the closing underscore
    }
    else {
      putchar(*pos);  //print non-placeholder characters
      pos++;
    }
  }
}

//reduced size cleaner func
void parseAndPrint(const char * filename, catarray_t * cats, int noReuse) {
  FILE * f = openFile(filename);
  size_t len = 0;
  char * line = NULL;
  usedWords usedWordsList = {NULL, 0};  //track previously used words

  while (getline(&line, &len, f) >= 0) {
    processLine(line, cats, noReuse, &usedWordsList);
  }

  freeUsedWords(&usedWordsList);
  free(line);
  fclose(f);
}

int wordAlreadyUsed(usedWords * usedWordsList, const char * word) {
  for (size_t i = 0; i < usedWordsList->n_used; i++) {
    if (strcmp(usedWordsList->usedWords[i], word) == 0) {
      return 1;  //word has already been used
    }
  }
  return 0;  //word has not been used
}

void removeUsedWord(catarray_t * cats, const char * category, const char * word) {
  for (size_t i = 0; i < cats->n; i++) {
    if (strcmp(cats->arr[i].name, category) == 0) {
      for (size_t j = 0; j < cats->arr[i].n_words; j++) {
        if (strcmp(cats->arr[i].words[j], word) == 0) {
          //   move the last word to the current position And reduce
          //          free(cats->arr[i].words[j]);
          //cats->arr[i].words[j] = NULL;
          //          printf("1%s1", (cats->arr[i].words[j]));
          free(cats->arr[i].words[j]);
          //cats->arr[i].words[j] = cats->arr[i].words[cats->arr[i].n_words - 1];
          //cats->arr[i].words[cats->arr[i].n_words - 1] = NULL;
          //
          //cats->arr[i].n_words--;
          // cats->arr[i].words[j] = "";
          //remove the word and move everything afterwords 1 step forward
          for (size_t k = j; k < cats->arr[i].n_words - 1; k++) {
            //            printf("2%s2", (cats->arr[i].words[k]));
            cats->arr[i].words[k] = cats->arr[i].words[k + 1];
            // printf("3%s3", (cats->arr[i].words[k]));
          }
          cats->arr[i].n_words--;
          cats->arr[i].words = realloc(
              cats->arr[i].words, cats->arr[i].n_words * sizeof(*(cats->arr[i].words)));
          //          printCatArray(cats);
          return;
        }
      }
    }
  }
}

//Retrieve a previously used word based on an index
const char * getPreviousWord(usedWords * usedWordsList, size_t index) {
  if (index == 0 || index > usedWordsList->n_used) {
    fprintf(stderr, "Error. Invalid reference(point1)\n");
    exit(EXIT_FAILURE);
  }
  return usedWordsList->usedWords[usedWordsList->n_used - index];
}
