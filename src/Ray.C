#include <cmath>

#include "Point.h"
#include "Ray.h"

sauron::Ray::Ray(Point &ending_point)
    : _starting_point{0, 0, 0},
      _ending_point(ending_point),
      _direction(_ending_point - _starting_point){

    setNorm();
    normalizeDirection();
}
sauron::Ray::Ray(Point &starting_point, Point &direction, double &distance)
    : _starting_point(starting_point),
      _direction(direction){

    normalizeDirection();
    _ending_point = _starting_point + (direction* distance);
    setNorm();
}
sauron::Ray::Ray(Point &starting_point, Point &ending_point)
    : _starting_point(starting_point),
      _ending_point(ending_point),
      _direction(_ending_point - _starting_point){

    setNorm();
    normalizeDirection();
}

void sauron::Ray::setNorm() {

  auto vector = _ending_point - _starting_point;
  _norm = calculateNorm(vector);
}

double sauron::Ray::calculateNorm(Point &point) {
  return sqrt(point.x * point.x + point.y * point.y + point.z * point.z);
}

void sauron::Ray::normalizeDirection() {
  if (isDirectionNormalized()) {
    // direction is already normalized
    // now need to do it again
  } else
    _direction = _direction / calculateNorm(_direction);
}

bool sauron::Ray::isDirectionNormalized() {
  return std::fabs(calculateNorm(_direction) - 1) < TOLERANCE;
}

void sauron::Ray::setNewDirection(Point &new_direction) {
  _direction = new_direction;
}

void sauron::Ray::moveStartingPoint(Point &new_starting_point) {
  _starting_point = new_starting_point;
}

void sauron::Ray::moveEndingPoint(Point &new_ending_point) {
  _ending_point = new_ending_point;
}
