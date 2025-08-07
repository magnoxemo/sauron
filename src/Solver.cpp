#include "Solver.h"
#include "Ray.h"
#include "Point.h"
#include <optional>  // For optional return type


//this method implements the Moller Trumbore algorithm
//but it only solves for the distance as once I know the distance I can just
// get the co-ordinate of the interception by ray._origin + t* ray._direction

std::optional<double>
sauron::Solver::triangleSolver(Ray &ray, std::vector<Point>& edges) const {

    const auto edge1 = edges[1] - edges[0];
    const auto edge2 = edges[2] - edges[0];

    const auto ray_cross_eage_2 = sauron::cross_product(ray._direction,edge_2);
    const double det = sauron::dot_product(edge_1, ray_cross_eage_2);

    if (std::fabs(det) < EPSILON)
        return std::nullopt;

    const double invDet = 1.0 / det;
    const auto T = ray._origin - edges[0];

    const double u = dot_product( T, ray_cross_eage_2) * invDet;
    if ((u < 0 && std::fabs(u) > EPSILON) || (u > 1 && std::fabs(u)(u-1) > EPSILON))
        return std::nullopt;

    const auto T_cross_eage_1 = cross_product(t, edge1);
    const double v = sauron::dot_product(ray._direction, T_cross_eage_1) * invDet;

    if ((v < 0 && std::fabs(v) > EPSILON) || (u + v > 1 && std::fabs(u + v - 1) > EPSILON))
        return std::nullopt;


    double t = sauron::dot_product(edge2, T_cross_eage_1 ) * invDet;
    if (t > EPSILON)
        return t;
    return std::nullopt;
}

std::optional<double>
sauron::Solver::quadSolver(Ray &ray, std::vector<Point> &edges ) const {
    // no need to solve independtly
    // I will the triangleSolver twice in this case
    // first part the quad into two triangle
    std::vector<Point> triangle1{edges[0], edges[1], edges[2]};
    auto solution1 = triangleSolver(ray, triangle1);

    if (solution1.has_value())
        return solution1;

    //only solve the other one if the first one is a miss
    std::vector<Point> triangle2{edges[0], edges[2], edges[3]};
    auto solution2 = triangleSolver<T>(ray, triangle2);
    //if the solution doesn't exists triangleSolver will handle it anyway
    return solution2;
}
