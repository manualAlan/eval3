#ifndef MYVECTOR_H
#define MYVECTOR_H

//write a struct here
//it should have a tag of vector_tag
//and should have 3 doubles named x, y, and z.
struct vector_tag {
  double x;
  double y;
  double z;
};
//YOUR CODE HERE
typedef struct vector_tag vector_t;
//write a typedef here which makes vector_t
//and alias for struct vector_tag

//YOUR CODE HERE

// you shouldnt need to modify these
double dot_product(vector_t v1, vector_t v2);
vector_t cross_product(vector_t v1, vector_t v2);

#endif
