#ifndef LIBMESH_TRACK_LENGTH_RAY_H
#define LIBMESH_TRACK_LENGTH_RAY_H

#include "Vector.h"

class Ray : public Vector3D {
public:
    Ray(Point &origin, Vector3D &direction);

    void moveRayToNewDirection(double t);

    void moveRayToNewDirection(double t, Vector3D &direction);

    Point getCurrentPoint() { return _current_point; }

    Point getPointAlongPath(double t);


    Point _origin;
    Point _current_point;
    Vector3D _direction;


};

#endif
