#include <cmath>
#include <omp.h>
#include <mpi.h>
#include <iostream>


#include "libmesh/libmesh.h"
#include "libmesh/point.h"
#include "libmesh/elem.h"

#include "Point.h"
#include "Ray.h"


std::vector<unsigned int,double>
sauron::MiddleEarth::parallelNazgulSolver(Point& current_point, Point& destination_point, sauron::Solver& solver){

    sauron::Ray forward_ray(current_point, destination_point );
    sauron::Ray backward_ray (destination_point, current_point);

    auto forward_dir = forward_ray.getDirection();
    auto reverse_dir = backward_ray.getDirection();

    //element in the current point
    auto starting_element = locateElementInMesh(current_point);
    auto destination_element = locateElementInMesh(destination_point);

    /*TO DO:
     * check if the element is valid */

    //TO DO: implement the clustering algorithm from snitch
    // also check it's solving for the forward direction point
    solveOneElement(forward_ray, starting_element);
    solveOneElement(backward_ray, starting_element);

}

template<typename T>
sauron::MiddleEarth::solveOneElement(sauron::Ray& ray, libMesh::Elem* element){

    for (const auto side_id: element->n_sides()) {
        std::vector<sauron::Point> vectecies_on_this_side;
        for (const auto node: element->nodes_on_sides(side_id)){
            auto p = elem->point(node);
            vectecies_on_this_side.push_back(sauron::convertLibMeshPointToSauronPoint(p));
        }

        //now check how many vertecies are there if 3 then call the triangular solver if 4 then call the quad solver
        //if else i will throw an error as I am lazy and haven't implemented solver for other elements
        //TO DO : this is where I am gonna implement the openmp parallerlism
        if (vectecies_on_this_side.size() == 3 ){
            //three point means triangle
            auto solution = solver.triangleSolver(ray, vectecies_on_this_side );
            return solution;
        }
        else if (vectecies_on_this_side.size() == 4){
            auto solution = solver.quadSolver(ray, vectecies_on_this_side );
            return solution;
        }
        else{
            std::cerr<<"For "<< element->type()<< "type "<<" I don't have a solver. It needs to be either Triangular or Quad \n";
            return ;
        }


    }
}