
#ifndef LIBMESH_TRACK_LENGTH_SOLVER_H
#define LIBMESH_TRACK_LENGTH_SOLVER_H

#include <optional>
#include <vector>

namespace sauron{

    //forward declare Point and Ray
    struct Point;
    class Ray;

    /*this solver class solves for the ray intersction point
     * and distance in an libMesh element
    */
    class Solver{

    public:
        Solver();
        //maybe it will be better to create a general solver class which
        //will the respective solver based the type of plane we would be solving
        std::optional<double> triangleSolver(sauron::Ray &ray, std::vector <sauron::Point> &edges) const;
        std::optional<double> quadSolver(sauron::Ray &ray, std::vector <sauron::Point> &edges) const ;

        static constexpr double EPSILON = 1e-10;
    };

}

#endif
