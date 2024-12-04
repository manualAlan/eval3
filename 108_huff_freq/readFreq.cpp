#include "readFreq.h"

#include <stdio.h>

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

void printSym(std::ostream & s, unsigned sym) {
  if (sym > 256) {
    s << "INV";
  }
  else if (sym == 256) {
    s << "EOF";
  }
  else if (isprint(sym)) {
    char c = sym;
    s << "'" << c << "'";
  }
  else {
    std::streamsize w = s.width(3);
    s << std::hex << sym << std::dec;
    s.width(w);
  }
}
uint64_t * readFrequencies(const char * fname) {
  uint64_t * res = new uint64_t[257];
  for (size_t i = 0; i < 257; i++) {
    res[i] = 0;
  }
  std::ifstream ist(fname);
  assert(ist.is_open());
  int i;
  while ((i = ist.get()) != EOF) {
    ++res[i];
  }
  res[256] = 1;
  return res;

  //WRITE ME!
}
