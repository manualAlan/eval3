#ifndef RAND_STORY_H
#define RAND_STORY_H
#include <stddef.h>  //
#include <stdio.h>

#include "provided.h"
// to track previously used words
struct usedWords_tag {
  char ** usedWords;
  size_t n_used;
};
typedef struct usedWords_tag usedWords;
void printCatArray(const catarray_t * catarray);
void addWordToList(char *** list, size_t * n_words, const char * word);
const char * handleBackReference(const char * category, usedWords * usedWordsList);

category_t * findOrCreateCategory(catarray_t * cats, const char * name);
void freeUsedWords(usedWords * usedWordsList);
catarray_t * parseWords(const char * filename);
FILE * openFile(const char * filename);
void freeCatArray(catarray_t * cats);
int categoryExists(catarray_t * cats, const char * category);
//void parseAndPrint(const char * filename, catarray_t * cats);
//int wordAlreadyUsed(usedWords * usedWordsList, const char * word);
//void removeUsedWord(catarray_t * cats, const char * category, const char * word);

void parseAndPrint(const char * filename, catarray_t * cats, int noReuse);
void removeUsedWord(catarray_t * cats, const char * category, const char * word);
const char * getPreviousWord(usedWords * usedWordsList, size_t index);
int wordAlreadyUsed(usedWords * usedWordsList, const char * word);
#endif
