#ifndef __KV_H__
#define __KV_H__
#include <stdlib.h>

struct _kvpair_t {
  char * key;
  char * value;  //DEFINE ME!
};
typedef struct _kvpair_t kvpair_t;

struct _kvarray_t {
  //DEFINE ME!
  kvpair_t * pairs;
  size_t length;
};
typedef struct _kvarray_t kvarray_t;

kvarray_t * readKVs(const char * fname);

void freeKVs(kvarray_t * pairs);

void printKVs(kvarray_t * pairs);

char * lookupValue(kvarray_t * pairs, const char * key);

#endif
