#include <cmath>

#include "Point.h"
#include "Ray.h"

sauron::Ray(Point &ending_point);
sauron::Ray(Point &starting_point, Point &direction, double &distance);
sauron::Ray(Point &starting_point, Point &ending_point);

void sauron::Ray::setNorm() {

  auto vector = _ending_point - _starting_point;
  _norm = calculateNorm(vector);
}

double sauron::Ray::calculateNorm(Point &point) {
  return sqrt(point.x * point.x + point.y * point.y + point.z * point.z);
}

Point
sauron::Ray::getDirection(){
    return _diraction;
}

void
sauron::Ray::normalizeDirection() {
  if (isDirectionNormalized()) {
    // direction is already normalized
    // now need to do it again
  } else
    _direction = _direction / calculateNorm(_direction);
}

bool
sauron::Ray::isDirectionNormalized() {
  return std::fabs(calculateNorm(_direction) - 1) < TOLERANCE;
}

void
sauron::Ray::setNewDirection(Point &new_direction) {
  _direction = new_direction;
}

void
sauron::Ray::moveStartingPoint(Point &new_starting_point) {
  _starting_point = new_starting_point;
}

void
sauron::Ray::moveEndingPoint(Point &new_ending_point) {
  _ending_point = new_ending_point;
}