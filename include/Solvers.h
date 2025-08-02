
#ifndef LIBMESH_TRACK_LENGTH_SOLVER_H
#define LIBMESH_TRACK_LENGTH_SOLVER_H
namespace sauron{

    //forward declare Point and Ray
    struct Point;
    class Ray;
    namespace libMesh{
        Elem;
    }

    /*this solver class solves for the ray intersction point
     * and distance in an libMesh element
    */
    class Solver(){

        Solver();
        //maybe it will be better to create a general solver class which
        //will the respective solver based the type of plane we would be solving
        template <typename T> solver(Ray& ray, libMesh::Elem * element);
        template <typename T> triangleSolver(Ray &ray, std::vector <Point> &edges) const;
        template <typename T> quadSolver(Ray &ray, std::vector <Point> &edges) const ;

        static constexpr double EPSILON = 1e-10;
    }

}

#endif
