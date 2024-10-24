#ifndef RAND_STORY_H
#define RAND_STORY_H

#include <stddef.h>  // for size_t

#include "provided.h"
// Struct to track previously used words
struct usedWords_tag {
  char ** usedWords;
  size_t n_used;
};
typedef struct usedWords_tag usedWords;

// Function to add a word to a dynamically allocated list
void addWordToList(char *** list, size_t * n_words, const char * word);

// Function to find or create a category in catarray_t
category_t * findOrCreateCategory(catarray_t * cats, const char * name);

// Function to parse the words file and return a catarray_t
catarray_t * parseWords(const char * filename);

// Function to free the memory allocated for the catarray_t
void freeCatArray(catarray_t * cats);

// Function to parse the story template and print the output
void parseAndPrint(const char * filename, catarray_t * cats);

// Function to retrieve a previously used word based on an index
const char * getPreviousWord(usedWords * usedWordsList, size_t index);

#endif
