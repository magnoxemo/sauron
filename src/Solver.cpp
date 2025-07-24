#include "Solver.h"
#include "Vector.h"


//this method implements the Moller Trumbore algorithm
template <typename T>
Solver::triangleSolver(Ray & ray, std::vector<Point>& edges) const {

    const auto edge_1 = edges[1] - edges[0];
    const auto edge_2 = edges[2] - edges[0];
    const auto T = ray._direction - edges[0];

    const auto Q = T.crossProduct(edge_1);
    const auto P = D.crossProduct(edge_2);

    auto solution =  Vector3D(Q.dotProduct(edge_2),
                              P.dotProduct(T),
                              Q.dotProduct(ray._direction)
                              )/P.dotProduct(edge_1);

    //if barycentric co-ordinate u<=0 or v<=0 or (v+u)>1 the ray wouldn't interset the triangle
    if ( (solution[1]+solution[2]>1) or  solution[1]<=EPSILON solution[2]<=EPSILON){
        return -1
    }
    else
        return solution;

}
