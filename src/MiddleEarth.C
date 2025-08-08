#include <cmath>
#include <omp.h>
#include <iostream>
#include <atomic>


#include "libmesh/libmesh.h"
#include "libmesh/point.h"
#include "libmesh/elem.h"

#include "Point.h"
#include "Ray.h"
#include "MiddleEarth.h"
#include "Mesh.h"
#include "Solver.h"


void
sauron::MiddleEarth::get_nodes_on_a_side(const libMesh::Elem* element,
                         unsigned int side_id,
                         std::vector<sauron::Point>& vectecies_on_this_side ){

    #pragma omp prallel for
    {
        for (const auto node: element->nodes_on_side(side_id)){
            auto p = element->point(node);
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
    auto starting_element = _mesh.locateElementInMesh(current_point);
    auto destination_element = _mesh.locateElementInMesh(destination_point);

    /*TO DO:
     * check if the element is valid */

    //TO DO: implement the clustering algorithm from snitch
    // also check it's solving for the forward direction point

    bool ray_solving_state = true;
    //need to pick up a better thing
    double totoal_track_length = sauron::get_distance(current_point, destination_point );
    double dist = 0.0 ;
    while (dist <= totoal_track_length){

        auto [forward_side_id, forward_ray_segment] = solveOneElement(forward_ray, starting_element).value();
        auto [reverse_side_id, reverse_ray_segment] = solveOneElement(backward_ray, destination_element).value();


        //check if they have reached to the same element or not
        if (forward_ray_segment>0){
            intercepted_element_ids.push_back(starting_element->id());
            ray_segments.push_back(forward_ray_segment);
            dist+=forward_ray_segment;
        }
        if (reverse_ray_segment>0){
            intercepted_element_ids.push_back(destination_element->id());
            ray_segments.push_back(reverse_ray_segment);
            dist+=reverse_ray_segment;
        }



        //get new elements
        starting_element = starting_element->neighbor_ptr(forward_side_id);
        destination_element = destination_element->neighbor_ptr(reverse_side_id);

        //update_ray
        forward_ray._starting_point = forward_ray._starting_point +  forward_ray._direction *forward_ray_segment;
        backward_ray._starting_point = backward_ray._starting_point +  backward_ray._direction * reverse_ray_segment;

    }
    return std::make_pair(intercepted_element_ids, ray_segments );
}



//solves for one element
//returns the side_id and ray segment
std::optional<std::pair<unsigned int, double>>
sauron::MiddleEarth::solveOneElement(sauron::Ray& ray, const libMesh::Elem* element){

    std::atomic<bool> is_solution_found(false);
    std::pair<unsigned int, double> result;

#pragma omp parallel for shared(is_solution_found)
    for (unsigned int side_id = 0; side_id < element->n_sides(); ++side_id) {

        if (is_solution_found.load())
            continue;

        std::vector<sauron::Point> vertices_on_this_side;
        get_nodes_on_a_side(element, side_id, vertices_on_this_side);

        std::optional<double> t;
        if (vertices_on_this_side.size() == 3)
            t = _solver.triangleSolver(ray, vertices_on_this_side);
        else if (vertices_on_this_side.size() == 4)
            t = _solver.quadSolver(ray, vertices_on_this_side);
        else {
            std::cerr << "Unsupported element with " << vertices_on_this_side.size() << " vertices.\n";
            continue;
        }

        if (t.has_value()) {
#pragma omp critical
            {
                if (!is_solution_found.load()) {
                    result = std::make_pair(side_id, t.value());
                    is_solution_found.store(true);
                }
            }
        }
    }

    if (is_solution_found.load())
        return result;

    return std::nullopt;
}
