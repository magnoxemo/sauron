#ifndef SAURON_MIDDLE_EARTH_H
#define SAURON_MIDDLE_EARTH_H

namespace sauron{

    class Ray;
    struct Point;
    class Solver;
    class UnstructuredMesh; // maybe not the best name

    /*
     * This class is for propagating ray for one point to a target point.
     * it will implement the nearest search to find the list of element
     * thorough which this ray passes through
     *
     * also needs better naming + should come up with a parallel solution
     * maybe start from the starting and ending point at the same time?
     * do a parallel search
    */

    class MiddleEarth{
        MiddleEarth(UnstructedMesh& mesh);

        //this function implements the parallel openmp solver
        //algorithm:
        //First layer of paralleism MPI: start from both end.
        //2nd layer of paralleism: parallel solve and search
        std::vector<int,double> parallelNazgulSolver(Point& current_point, Point& destination_point);

        //ref of the mesh for point locator
        UnstructedMesh& _mesh;
        static libMesh::PointLocatorTree _point_locator_object;
    };
}

#endif
