#ifndef __RAND_STORY_H__
#define __RAND_STORY_H__

#include <stdio.h>
#include <stdlib.h>

#include "provided.h"
catarray_t * parseWords(const char * filename);
void freeCatArray(catarray_t * categories);
void parse_cat(char * filename);

catarray_t * parseWords(const char * filename);
void freeCatArray(catarray_t * cats);
void parseAndPrint(const char * filename, catarray_t * cats);
#endif
