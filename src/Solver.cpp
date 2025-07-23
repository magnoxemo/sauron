#include "Solver.h"
#include "Vector.h"

namespace Bijron{

    template <typename T>
    Solver::triangleSolver(Ray & ray, std::vector<Point>& edges) const {

        const auto edge_1 = edges[1]-edges[0];
        const auto edge_2 = edges[2]-edges[0];

        auto h = ray._direction.crossProduct(edge_2);
        auto a = h.dotProduct(eage_1);
        if (a.calculateNorm()<TOLERANCE)
            return -1;

    }
}