#ifndef SAURON_MIDDLE_EARTH_H
#define SAURON_MIDDLE_EARTH_H

#include <optional>
#include "Solver.h"

namespace libMesh{
    class Elem;
}


namespace sauron {

class Ray;
struct Point;
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

class MiddleEarth {

public:
    MiddleEarth(UnstructuredMesh &mesh):
          _mesh(mesh){

  }

  /*this function implements the parallel openmp solver algorithm
   * First layer of paralleism MPI: start from both end.
   * 2nd layer of paralleism: parallel solve and search
   * input: starting point and destination point of the ray
   * return:
   * element_ids and their respective track length
   */

  std::pair<std::vector<unsigned int>, std::vector<double>>
  parallelNazgulSolver(Point &current_point, Point &destination_point);

private:
  void get_nodes_on_a_side(const libMesh::Elem *element, unsigned int side_id,
                                  std::vector<Point> &vectecies_on_this_side);

  // splits the into one forward direction and another in backward direction
  std::pair<sauron::Ray, sauron::Ray> splitRay(sauron::Point& origin,sauron::Point& destination_point);

  // if the ray intercepted with any forward face
  void rayMadeProgress(std::optional<std::pair<unsigned int, double>>& solution,
                       sauron::Ray* ray,
                       bool* progress_flag,
                       double* distance_counter,
                       const libMesh::Elem** element,
                       std::vector<unsigned int>* intercepted_element_ids,
                       std::vector<double>* ray_segments);

  // solves for one element returns the side_id and ray segment
  std::optional<std::pair<unsigned int, double>>
  solveOneElement(sauron::Ray &ray, const libMesh::Elem *element);

  // ref of the mesh for point locator
  UnstructuredMesh &_mesh;

  Solver _solver;

  constexpr static unsigned int _mpi_world_size = 3;
};
} // namespace sauron

#endif
