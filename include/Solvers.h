
#ifndef LIBMESH_TRACK_LENGTH_SOLVER_H
#define LIBMESH_TRACK_LENGTH_SOLVER_H

class Point;
class Ray;

class Solver(){
    const double EPSILON = 0.000001;
    template <typename T> triangleSolver(Ray &ray, std::vector <Point> &edges) const;
    template <typename T> quadSolver(Ray &ray, std::vector <Point> &edges) const ;

}
#endif
