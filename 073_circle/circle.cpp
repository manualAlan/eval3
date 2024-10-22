#include "circle.hpp"

#include <algorithm>
#include <cmath>
void Circle::move(double dx, double dy) {
  center.move(dx, dy);
}

double Circle::intersectionArea(const Circle & otherCircle) const {
  double d = center.distanceFrom(otherCircle.center);
  if (d >= radius + otherCircle.radius) {
    return 0.0;  // No intersection
  }
  else if (d <= std::fabs(radius - otherCircle.radius)) {
    double smallerRadius = std::min(radius, otherCircle.radius);
    return M_PI * smallerRadius * smallerRadius;  // One circle is inside the other
  }
  else {
    double r1 = radius;
    double r2 = otherCircle.radius;
    double part1 = r1 * r1 * std::acos((d * d + r1 * r1 - r2 * r2) / (2 * d * r1));
    double part2 = r2 * r2 * std::acos((d * d + r2 * r2 - r1 * r1) / (2 * d * r2));
    double part3 =
        0.5 * std::sqrt((-d + r1 + r2) * (d + r1 - r2) * (d - r1 + r2) * (d + r1 + r2));
    return part1 + part2 - part3;
  }
}
