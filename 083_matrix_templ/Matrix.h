#ifndef MATRIX_H
#define MATRIX_H
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <vector>

template<typename T>
class Matrix {
 private:
  int rows;
  int columns;
  std::vector<std::vector<T> > data;

 public:
  // Default constructor
  Matrix() : rows(0), columns(0), data() {}

  // Constructor with specified dimensions
  Matrix(int r, int c) : rows(r), columns(c), data(r, std::vector<T>(c)) {
    assert(r >= 0 && c >= 0);  // Handle special case: negative dimensions
  }

  // Copy constructor
  Matrix(const Matrix & rhs) : rows(rhs.rows), columns(rhs.columns), data(rhs.data) {}

  // Destructor
  ~Matrix() {}

  // Assignment operator
  Matrix & operator=(const Matrix & rhs) {
    if (this != &rhs) {
      rows = rhs.rows;
      columns = rhs.columns;
      data = rhs.data;
    }
    return *this;
  }

  // Get the number of rows
  int getRows() const { return rows; }

  // Get the number of columns
  int getColumns() const { return columns; }

  // Overload the equality operator
  bool operator==(const Matrix & rhs) const {
    if (rows != rhs.rows || columns != rhs.columns) {
      return false;
    }
    return data == rhs.data;
  }

  // Overload the addition operator
  Matrix operator+(const Matrix & rhs) const {
    assert(rows == rhs.rows && columns == rhs.columns);  // Check for matching dimensions
    Matrix result(rows, columns);
    for (int i = 0; i < rows; ++i) {
      for (int j = 0; j < columns; ++j) {
        result.data[i][j] = data[i][j] + rhs.data[i][j];
      }
    }
    return result;
  }

  // Overload the subscript operator to access elements
  std::vector<T> & operator[](int index) {
    assert(index >= 0 && index < rows);  // Check for out-of-bounds access
    return data[index];
  }

  const std::vector<T> & operator[](int index) const {
    assert(index >= 0 && index < rows);  // Check for out-of-bounds access
    return data[index];
  }

  // Friend function to overload the output stream operator
  friend std::ostream & operator<<(std::ostream & os, const Matrix & matrix) {
    os << "[ ";
    for (int i = 0; i < matrix.rows; ++i) {
      os << "{";
      for (int j = 0; j < matrix.columns; ++j) {
        os << matrix.data[i][j];
        if (j < matrix.columns - 1) {
          os << ", ";
        }
      }
      os << "}";
      if (i < matrix.rows - 1) {
        os << ",\n  ";
      }
    }
    os << " ]";
    return os;
  }
};

#endif  // MATRIX_H
