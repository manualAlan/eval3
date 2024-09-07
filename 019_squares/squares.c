void squares(int size1, int x_offset, int y_offset, int size2) {
  int w;
  int h;
  if (size1 > (x_offset + size2)) {
    w = size1;
  }
  else {
    w = (x_offset + size2);
  }
  if (size1 > (y_offset + size2)) {
    h = size1;
  }
  else {
    h = (y_offset + size2);
  }
  for (int y = 0; y < h; y++) {
    for (int x = 0; x < w; x++) {
      // Check if either
      // ((x is between x_offset and x_offset + size)
      if (((x >= x_offset && x < x_offset + size2) &&
           (y == y_offset || y == y_offset + size2 - 1)) ||

          // OR
          // ((y is between y_offset and y_offset + size2) AND
          //  x is equal to either x_offset OR x_offset + size2 - 1)
          ((y >= y_offset && y < y_offset + size2) &&
           (x == x_offset || x == x_offset + size2 - 1))) {
        // If so, print a *
        printf("*");
      }
      // Check if either
      // x is less than size1 AND (y is either 0 or size1-1)
      // OR
      // y is less than size1 AND (x is either 0 or size1-1)
      else if ((x < size1 && (y == 0 || y == size1 - 1)) ||
               (y < size1 && (x == 0 || x == size1 - 1))) {
        // If so, print a #
        printf("#");
      }
      // Else, print a space
      else {
        printf(" ");
      }
    }
    // When you finish counting x from 0 to w, print a newline
    printf("\n");
  }
  //     y is equal to either y_offset OR y_offset + size2 - 1 ))
  //compute the max of size1 and (x_offset + size2).  Call this w

  //compute the max of size1 and (y_offset + size2).  Call this h

  //count from 0 to h. Call the number you count with y

  //count from 0 to w. Call the number you count with x

  //check if  EITHER
  //    ((x is between x_offset  and x_offset +size2) AND
  //     y is equal to either y_offset OR y_offset + size2 - 1 )
  //  OR
  //    ((y is between y_offset and y_offset + size2) AND
  //     x is equal to either x_offset OR x_offset + size2 -1)
  // if so, print a *

  //if not,
  // check if EITHER
  //    x is less than size1 AND (y is either 0 or size1-1)
  // OR
  //    y is less than size1 AND (x is either 0 or size1-1)
  //if so, print a #

  //else print a space
  //when you finish counting x from 0 to w,
  //print a newline
}
