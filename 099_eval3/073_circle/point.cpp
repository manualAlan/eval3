#include "point.hpp"

#include <cmath>  // for sqrt

// Method to calculate the distance between two points
double Point::distanceFrom(const Point & p) const {
  double dx = x - p.x;
  double dy = y - p.y;
  return std::sqrt(dx * dx + dy * dy);
}
