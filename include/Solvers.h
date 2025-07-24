
#ifndef LIBMESH_TRACK_LENGTH_SOLVER_H
#define LIBMESH_TRACK_LENGTH_SOLVER_H
#define EPSILON 0.000001

class Point;
class Ray;

class Solver()

{
public:

Point triangleSolver(Ray &ray, std::vector <Point> &edges) const;

Point quadSolver(Ray &ray, std::vector <Point> &edges) const ;

}
#endif
