#include <stdio.h>
#include <stdlib.h>

void rotateMatrix(char grid[10][10]) {
  int n = 9;
  for (int a = 0; a < 5; a++) {
    for (int b = a; b < 9 - a; b++) {
      char tempVal = grid[a][b];
      grid[a][b] = grid[n - b][a];
      grid[n - b][a] = grid[n - a][n - b];
      grid[n - a][n - b] = grid[b][n - a];
      grid[b][n - a] = tempVal;
    }
  }
}

int main(int argc, char ** args) {
  if (argc != 2) {
    fprintf(stderr, "arguments number wrong\n");
    return EXIT_FAILURE;
  }

  FILE * filePtr = fopen(args[1], "r");
  if (filePtr == NULL) {
    fprintf(stderr, "file not opening\n");
    return EXIT_FAILURE;
  }

  int charRead = fgetc(filePtr);
  if (charRead == EOF) {
    fprintf(stderr, "file empty\n");
    return EXIT_FAILURE;
  }

  char matrix[10][10];
  int rowNum = 0, colNum = 0;

  while (charRead != EOF) {
    if (rowNum >= 10) {
      fprintf(stderr, "too many rows\n");
      return EXIT_FAILURE;
    }

    if (colNum == 10) {
      colNum = 0;
      rowNum++;
      if (charRead != '\n') {
        fprintf(stderr, "missing newline\n");
        return EXIT_FAILURE;
      }
    }
    else {
      if (charRead < 32 || charRead > 126) {
        fprintf(stderr, "invalid character found: %d\n", charRead);
        return EXIT_FAILURE;
      }

      if (charRead == '\n') {
        fprintf(stderr, "less columns\n");
        return EXIT_FAILURE;
      }
      matrix[rowNum][colNum] = charRead;
      colNum++;
    }
    charRead = fgetc(filePtr);
  }

  if (rowNum < 10) {
    fprintf(stderr, "not enough rows\n");
    return EXIT_FAILURE;
  }
  if (fgetc(filePtr) != EOF) {
    fprintf(stderr, "file has too many characters\n");
    return EXIT_FAILURE;
  }
  rotateMatrix(matrix);
  fclose(filePtr);
  // Printer
  for (int x = 0; x < 10; x++) {
    for (int y = 0; y < 10; y++) {
      if (matrix[x][y] == '\0' || matrix[x][y] < 32 || matrix[x][y] > 126) {
        fprintf(
            stderr, "Error: null character found in matrix at position [%d][%d]\n", x, y);
        return EXIT_FAILURE;  // Exit with failure if null is found
      }
      printf("%c", matrix[x][y]);
    }
    printf("\n");
  }

  return EXIT_SUCCESS;
}