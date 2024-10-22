#ifndef VECTOR_HPP
#define VECTOR_HPP
#include <cmath>
#include <cstdio>

class Vector2D {
 private:
  double x;
  double y;

 public:
  //Default constructor
  Vector2D() : x(0), y(0) {}

  Vector2D(double init_x, double init_y) : x(init_x), y(init_y) {}

  double getMagnitude() const { return std::sqrt(x * x + y * y); }

  Vector2D operator+(const Vector2D & rhs) const {
    Vector2D result;
    result.x = this->x + rhs.x;
    result.y = this->y + rhs.y;
    return result;
  }

  Vector2D & operator+=(const Vector2D & rhs) {
    this->x += rhs.x;
    this->y += rhs.y;
    return *this;
  }

  double dot(const Vector2D & rhs) const { return this->x * rhs.x + this->y * rhs.y; }

  void print() const { std::printf("<%.2f, %.2f>", x, y); }
};

#endif
