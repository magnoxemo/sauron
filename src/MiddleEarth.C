#include <cmath>
#include <omp.h>
#include <mpi.h>
#include <iostream>


#include "libmesh/libmesh.h"
#include "libmesh/point.h"
#include "libmesh/elem.h"

#include "Point.h"
#include "Ray.h"


void get_nodes_on_a_side(libMesh::Elem* element,
                         unsigned int side_id,
                         std::vector<Point>& vectecies_on_this_side ){

    #pagma omp prallel
    {
        for (const auto node: element->nodes_on_sides(side_id)){
            auto p = elem->point(node);
            vectecies_on_this_side.push_back(sauron::convertLibMeshPointToSauronPoint(p));
        }
    };

}
//returns the element id vector and their respective track lengths
std::pair<std::vector<unsigned int>, std::vector<double>>
sauron::MiddleEarth::parallelNazgulSolver(Point& current_point, Point& destination_point, sauron::Solver& solver){

    std::vector<unsigned int> intercepted_element_ids;
    std::vector<double> ray_segments;

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

    bool ray_solving_state = true;
    while (ray_solving_state){

        auto forward_side_id, forward_ray_segment = solveOneElement(forward_ray, starting_element);
        auto reverse_side_id, reverse_ray_segment = solveOneElement(backward_ray, destination_element);


        //check if they have reached to the same element or not
        if ((starting_element->neighbor_side_ptr(forward_side_id)) == (destination_element->neighbor_side_ptr(reverse_side_id)))
            return std::make_pair(intercepted_element_ids, ray_segments );

        //load the data
        intercepted_element_ids.push_back(starting_element->id());
        intercepted_element_ids.push_back(destination_element->id());
        ray_segments.push_back(forward_ray_segment);
        ray_segments.push_back(reverse_ray_segment);

        //get new elements
        auto starting_element = starting_element->neighbor_side_ptr(forward_side_id);
        auto destination_element = destination_element->neighbor_side_ptr(reverse_side_id);

        //update_ray
        forward_ray._starting_point = forward_ray._starting_point + forward_ray_segment* forward_ray._direction;
        backward_ray._starting_point = backward_ray._starting_point + backward_ray* backward_ray._direction;

    }


}



//solves for one element
//returns the side_id and ray segment
std::pair<unsigned int, double>
sauron::MiddleEarth::solveOneElement(sauron::Ray& ray, libMesh::Elem* element){

     int side_id_of_the_intercepted_side;
     double track_length;
     std::atomic<bool> is_solution_found(false);

    #pagma omp parallel for shared (is_solution_found, side_id_of_the_intercepted_side, track_length)

    for (const auto side_id: element->n_sides()) {

        if (is_solution_found.found())
            continue;

        std::vector<sauron::Point> vectecies_on_this_side;
        get_nodes_on_a_side(element, side_id, vectecies_on_this_side);

        //now check how many vertecies are there if 3 then call the triangular solver if 4 then call the quad solver
        //if else i will throw an error as I am lazy and haven't implemented solver for other elements
        //TO DO : this is where I am gonna implement the openmp parallerlism

            if (vectecies_on_this_side.size() == 3 )
                //three point means triangle
                auto t = solver.triangleSolver(ray, vectecies_on_this_side );
            else if (vectecies_on_this_side.size() == 4)
                auto t = solver.quadSolver(ray, vectecies_on_this_side );
            else{
                std::cerr<<"For "<< element->type()<< "type "<<" I don't have a solver. It needs to be either Triangular or Quad \n";
            }
            #pragma omp parallel critical
            {
                if (!is_solution_found.found()){
                    if (t.has_value()){
                        track_length = t;
                        side_id_of_the_intercepted_side = side_id;
                        is_solution_found.store(true);
                    }
                }

            };
        #pragma omp cancellation point for

    }

    if (is_solution_found.found())
        return std::make_pair(side_id_of_the_intercepted_side,track_length);
    else
        return;

}