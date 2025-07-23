#include "Ray.h"

Ray::Ray(Point &origin,
         Vector3D &direction) :
        _origin(origin),
        _direction(direction) {}

void
Ray::moveRayToNewDirection(double t) {
    _current_point = addVectors(_current_point, _direction * t);
}

void
Ray::moveRayToNewDirection(double t, Vector3D &direction) {
    _current_point = addVectors(_current_point, direction * t);
}

Point
Ray::getPointAlongPath(double t) {
    return addVectors(_current_point, _direction * t);
}