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
        return -1 ;
    }
    else
        return solution;

}

template <typename T>
Solver::quadSolver(Ray &ray, std::vector <Point> &edges) const{
    // no need to solve independtly
    // I will the triangleSolver twice in this case
    // first part the quad into two triangle
    std::vector<Point> triangle_1 (edges[0], edges[1], edges[2]);
    auto solution_1 = triangelSolver(ray, triangle_1);

    //only solve the other one if the first one is a miss
    if (solution_1 !=-1){
        std::vector<Point> tirangle_2 (edges[0], edges[3], edges[2]);
        auto solution_2 = tiangleSolver(ray,triangle_2);
        //if the solution doesn't exists triangleSolver will handle it anyway
        return  solution_2;
    }
    return solution_1;
}
