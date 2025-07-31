#ifndef SAURON_RAY_H
#define SAURON_RAY_H

namespace sauron {

struct Point; //forward declaration

/* This class implements a standard ray class. I am gonna presume that a ray has
 * a starting point and an ending point and a direction. We should be able to
 * move a ray in a forward direction --> moving the end point in the direction
 */

class Ray {

public:
  // creates a ray that originates at the origin and ends at the end point
  Ray(Point &ending_point);
  /// creates a ray that originates at the a point and calculates the end
  /// point from direction and distance
  ///the direction needs to be normalized
  Ray(Point &starting_point, Point &direction, double &distance);
  /// creates a ray from a starting point and ending point
  Ray(Point &starting_point, Point &ending_point);

  void setNorm();

  double calculateNorm(Point & point) ;

  Point getDirection() { return _direction; }

  void normalizeDirection();

  bool isDirectionNormalized();

  void setNewDirection(Point &new_direction);

  void moveStartingPoint(Point &new_starting_point);

  void moveEndingPoint(Point &new_ending_point);

  Point getPointAlongTheRay(double t);

  // operator overloading section

  Point _starting_point;
  Point _ending_point;
  Point _direction;
  double _norm;

  static constexpr double TOLERANCE = 1e-10;
};
} // namespace sauron

#endif