#ifndef SAURON_MIDDLE_EARTH_H
#define SAURON_MIDDLE_EARTH_H

#include <optional>

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
        MiddleEarth (UnstructuredMesh& mesh);

        /*this function implements the parallel openmp solver algorithm
         * First layer of paralleism MPI: start from both end.
         * 2nd layer of paralleism: parallel solve and search
         * input: starting point and destination point of the ray
         * return:
         * element_ids and their respective track length
         */

        std::pair<std::vector<unsigned int>, std::vector<double>>
        parallelNazgulSolver(Point& current_point,
                             Point& destination_point,
                             sauron::Solver& solver);
    private:
        //
        void get_nodes_on_a_side(const libMesh::Elem* element,
                                 unsigned int side_id,
                                 std::vector<Point>& vectecies_on_this_side );

        //solves for one element returns the side_id and ray segment
        std::optional<std::pair<unsigned int, double>>
        solveOneElement(sauron::Ray& ray,
                        const libMesh::Elem* element);

        //ref of the mesh for point locator
        UnstructuredMesh& _mesh;

        Solver& _solver;

        //maybe not a good practice
        /*three mpi process
         * one master and two slave
         * two slave will over look the solving process
         * and the master will do the communication if the process is done or not */
        constexpr static unsigned int _mpi_world_size = 3;

    };
}

#endif
