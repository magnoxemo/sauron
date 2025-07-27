#include "Solver.h"
#include "Vector.h"
#include <optional>  // For optional return type


//this method implements the Moller Trumbore algorithm
template <typename T>
std::optional<Vector3D> Solver::triangleSolver(Ray &ray, std::vector<Point>& edges) const {

    const auto edge1 = edges[1] - edges[0];
    const auto edge2 = edges[2] - edges[0];

    const auto P = ray._direction.crossProduct(edge2);
    const double det = P.dotProduct(edge1);

    if (std::fabs(det) < EPSILON)
        return std::nullopt;

    const double invDet = 1.0 / det;
    const auto T = ray._origin - edges[0];

    const double u = T.dotProduct(P) * invDet;
    if (u < 0.0 || u > 1.0)
        return std::nullopt;

    const auto Q = T.crossProduct(edge1);
    const double v = ray._direction.dotProduct(Q) * invDet;
    if (v < 0.0 || (u + v) > 1.0)
        return std::nullptr;

    const double t = edge2.dotProduct(Q) * invDet;
    if (t > EPSILON) {
        return Vector3D(t, u, v);
    }

    return std::nullopt;
}

template <typename T>
std::optional<Vector3D> Solver::quadSolver(Ray &ray, std::vector<Point> &edges) const {
    // no need to solve independtly
    // I will the triangleSolver twice in this case
    // first part the quad into two triangle
    std::vector<Point> triangle1{edges[0], edges[1], edges[2]};
    auto solution1 = triangleSolver<T>(ray, triangle1);

    if (solution1.has_value())
        return solution1;

    //only solve the other one if the first one is a miss
    std::vector<Point> triangle2{edges[0], edges[2], edges[3]};
    auto solution2 = triangleSolver<T>(ray, triangle2);
    //if the solution doesn't exists triangleSolver will handle it anyway
    return solution2;
}
