#ifndef SAURON_POINT_H
#define SAURON_POINT_H

#include "libmesh/point.h"

namespace sauron {

// making a Point struct for my own sanity
struct Point {
  double x, y, z;
  constexpr static double tolerance = 10e-5;

  // Overloading the addition operator (+)
  Point operator+(const Point &other) const {
    return {x + other.x, y + other.y, z + other.z};
  }
  // Overloading the addition operator (+)
  Point operator+(double t) const { return {x + t, y + t, z + t}; }

  // Overloading the addition operator (+)
  Point operator-(const Point &other) const {
    return {x - other.x, y - other.y, z - other.z};
  }

  Point operator-(double t) const { return {x - t, y - t, z - t}; }

  // Overloading the addition operator (+)
  Point operator*(const Point &other) const {
    return {x * other.x, y * other.y, z * other.z};
  }

  Point operator*(double t) const { return {x * t, y * t, z * t}; }

  // Overloading the addition operator (+)
  Point operator/(const Point &other) const {
    return {x / other.x, y / other.y, z / other.z};
  }

  Point operator/(double t) const { return {x / t, y / t, z / t}; }
  // Overloading the equality operator (==)
  bool operator==(const Point &other) const {
    Point p = {x - other.x , y - other.y , z - other.z};
    if ((p*p).sum()< tolerance )
        return true;
    return false;
  }

  double sum() const { return x + y + z; }
};

Point convertLibMeshPointToSauronPoint(const libMesh::Point &point);
Point cross_product(const Point &point_a, const Point &point_b);
double dot_product(const Point &point_a, const Point &point_b);
double get_distance(const Point &point_a, const Point &point_b);

} // namespace sauron

#endif
