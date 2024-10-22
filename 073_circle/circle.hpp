#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "point.hpp"

class Circle {
 private:
  Point center;
  const double radius;

 public:
  Circle(const Point & p, double r) : center(p), radius(r) {}

  void move(double dx, double dy);

  double intersectionArea(const Circle & otherCircle) const;
};

#endif
