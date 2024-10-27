#ifndef RAND_STORY_H
#define RAND_STORY_H

#include <stddef.h>  //

#include "provided.h"
// to track previously used words
struct usedWords_tag {
  char ** usedWords;
  size_t n_used;
};
typedef struct usedWords_tag usedWords;
void printCatArray(const catarray_t * catarray);
void addWordToList(char *** list, size_t * n_words, const char * word);

category_t * findOrCreateCategory(catarray_t * cats, const char * name);

catarray_t * parseWords(const char * filename);

void freeCatArray(catarray_t * cats);

//void parseAndPrint(const char * filename, catarray_t * cats);
void parseAndPrint(const char * filename, catarray_t * cats, int noReuse);
void removeUsedWord(catarray_t * cats, const char * category, const char * word);
const char * getPreviousWord(usedWords * usedWordsList, size_t index);
int wordAlreadyUsed(usedWords * usedWordsList, const char * word);
#endif
