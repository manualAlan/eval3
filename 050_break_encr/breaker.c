#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

void count_frequencies(FILE * f, int * freq) {
  int c;
  while ((c = fgetc(f)) != EOF) {
    if (isalpha(c)) {
      c = tolower(c) - 'a';
      freq[c]++;
    }
  }
}

int find_most_frequent_letter(int * freq) {
  int max_count = 0;
  int most_frequent = 0;
  for (int i = 0; i < 26; i++) {
    if (freq[i] > max_count) {
      max_count = freq[i];
      most_frequent = i;
    }
  }
  return most_frequent;
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: breaker inputFileName\n");
    return EXIT_FAILURE;
  }

  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("Could not open file");
    return EXIT_FAILURE;
  }

  int freq[26] = {0};
  count_frequencies(f, freq);

  if (fclose(f) != 0) {
    perror("Failed to close the input file!");
    return EXIT_FAILURE;
  }

  int most_frequent_letter = find_most_frequent_letter(freq);

  int key = (most_frequent_letter - ('e' - 'a') + 26) % 26;

  printf("%d\n", key);
  return EXIT_SUCCESS;
}
