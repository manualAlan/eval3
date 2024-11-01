#ifndef MATRIX_H
#define MATRIX_H
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <vector>

template<typename T>
class Matrix {
 private:
  int rows;     // Use int instead of size_t
  int columns;  // Use int instead of size_t
  std::vector<std::vector<T> > data;

 public:
  // Default constructor
  Matrix() : rows(0), columns(0), data() {}

  // Constructor with specified dimensions
  Matrix(int r, int c) : rows(r), columns(c), data(r, std::vector<T>(c)) {}

  // Copy constructor
  Matrix(const Matrix & other) :
      rows(other.rows), columns(other.columns), data(other.data) {}

  // Destructor
  ~Matrix() {}

  // Assignment operator
  Matrix & operator=(const Matrix & other) {
    if (this != &other) {
      rows = other.rows;
      columns = other.columns;
      data = other.data;
    }
    return *this;
  }

  // Get the number of rows
  int getRows() const {  // Return int
    return rows;
  }

  // Get the number of columns
  int getColumns() const {  // Return int
    return columns;
  }

  // Overload the equality operator
  bool operator==(const Matrix & other) const {
    return (rows == other.rows && columns == other.columns && data == other.data);
  }

  // Overload the addition operator
  Matrix operator+(const Matrix & other) const {
    if (rows != other.rows || columns != other.columns) {
      throw std::invalid_argument("Matrix dimensions must match for addition");
    }
    Matrix result(rows, columns);
    for (int i = 0; i < rows; ++i) {
      for (int j = 0; j < columns; ++j) {
        result.data[i][j] = data[i][j] + other.data[i][j];
      }
    }
    return result;
  }

  // Overload the subscript operator to access elements
  std::vector<T> & operator[](int index) {
    if (index < 0 || index >= rows) {
      throw std::out_of_range("Index out of range");
    }
    return data[index];
  }

  const std::vector<T> & operator[](int index) const {
    if (index < 0 || index >= rows) {
      throw std::out_of_range("Index out of range");
    }
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
