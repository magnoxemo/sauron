#include <atomic>
#include <cmath>
#include <iostream>
#include <omp.h>

#include "libmesh/elem.h"
#include "libmesh/libmesh.h"
#include "libmesh/point.h"

#include "Mesh.h"
#include "MiddleEarth.h"
#include "Point.h"
#include "Ray.h"
#include "Solver.h"
#include "NumCornerNodes.h"

void sauron::MiddleEarth::get_nodes_on_a_side(
        const libMesh::Elem *element, unsigned int side_id,
        std::vector<sauron::Point> &vertices_on_this_side) {

    vertices_on_this_side.clear();

    auto num_corner_nodes = number_of_corner_nodes_on_a_side(element->type());

    if (num_corner_nodes != -1) {
        vertices_on_this_side.resize(num_corner_nodes);
        auto nodes = element->nodes_on_side(side_id);
        for (decltype(num_corner_nodes) node_index = 0; node_index < num_corner_nodes; node_index++) {
            auto p = element->point(nodes[node_index]);
            vertices_on_this_side[node_index] = sauron::convertLibMeshPointToSauronPoint(p);
        }
    } else
        std::cerr << "Unsupported element type" << element->type();
    vertices_on_this_side.shrink_to_fit();
}

std::pair<sauron::Ray, sauron::Ray>
sauron::MiddleEarth::splitRay(sauron::Point& origin,sauron::Point& destination_point){

    auto forward_direction = (destination_point - origin);
    auto backward_direction = (origin - destination_point);
    auto forward_ray = sauron::Ray(origin, forward_direction);
    auto backward_ray =  sauron::Ray (destination_point, backward_direction);

    return std::make_pair(forward_ray, backward_ray);
}

void
sauron::MiddleEarth::rayMadeProgress(std::optional<std::pair<unsigned int, double>>& solution,
                                     sauron::Ray* ray,
                                     bool* progress_flag,
                                     double* distance_counter,
                                     const libMesh::Elem** element,
                                     std::vector<unsigned int>* intercepted_element_ids,
                                     std::vector<double>* ray_segments){

    if (solution){
        auto [side_id, ray_segment] = solution.value();
        intercepted_element_ids->push_back((*element)->id());
        ray_segments->push_back(ray_segment);
        *distance_counter += ray_segment;
        *element = (*element)->neighbor_ptr(side_id);
        ray->_starting_point = ray->_starting_point + ray->_direction * ray_segment;
        *progress_flag = true;
    }
}

std::pair<std::vector<unsigned int>, std::vector<double>>
sauron::MiddleEarth::parallelNazgulSolver(Point &current_point,
                                          Point &destination_point) {

    std::vector<unsigned int> intercepted_element_ids;
    std::vector<double> ray_segments;

    auto starting_element = _mesh.locateElementInMesh(current_point);
    auto destination_element = _mesh.locateElementInMesh(destination_point);

    if (!starting_element || !destination_element) {
        return std::make_pair(intercepted_element_ids, ray_segments);
    }

    // if both elements are same then no need solve those repeatedly
    if (starting_element == destination_element) {
        auto forward_side_id = starting_element->id();
        auto forward_ray_segment = get_distance(current_point, destination_point);
        intercepted_element_ids.push_back(forward_side_id);
        ray_segments.push_back(forward_ray_segment);
        // should I add any check if track length == dist?
        return std::make_pair(intercepted_element_ids, ray_segments);
    }

    auto rays = splitRay(current_point, destination_point);
    auto &forward_ray = rays.first;
    auto &backward_ray = rays.second;

    double total_track_length = sauron::get_distance(current_point, destination_point);
    double dist = 0.0;

    bool progress_made = false;

    while (dist <= total_track_length) {
        progress_made = false;

        auto forward_solution = solveOneElement(forward_ray, starting_element);
        auto reverse_solution = solveOneElement(backward_ray, destination_element);

        rayMadeProgress(forward_solution, &forward_ray,  &progress_made, &dist, &starting_element, &intercepted_element_ids, &ray_segments);
        rayMadeProgress(reverse_solution, &backward_ray, &progress_made, &dist, &destination_element, &intercepted_element_ids, &ray_segments);

        if (!progress_made || (backward_ray._starting_point == forward_ray._starting_point))
            break; // need to come up with better way to avoid infinite loop
    }

    return std::make_pair(intercepted_element_ids, ray_segments);
}

std::optional<std::pair<unsigned int, double>>
sauron::MiddleEarth::solveOneElement(sauron::Ray &ray,
                                     const libMesh::Elem *element) {

    std::atomic<bool> is_solution_found(false);
    std::pair<unsigned int, double> result;
    const unsigned int num_sides = element->n_sides();

#pragma omp parallel for default(none) shared(num_sides, is_solution_found, result, ray, element) schedule(dynamic)
    for (unsigned int side_id = 0; side_id < num_sides; ++side_id) {
        if (is_solution_found.load())
            continue;

        std::vector<sauron::Point> vertices_on_this_side;
        get_nodes_on_a_side(element, side_id, vertices_on_this_side);

        std::optional<double> t;
        try {
            if (vertices_on_this_side.size() == 3)
                t = _solver.triangleSolver(ray, vertices_on_this_side);
            else if (vertices_on_this_side.size() == 4)
                t = _solver.quadSolver(ray, vertices_on_this_side);
        } catch (...) {
            continue;
        }

        if (t.has_value()) {
            bool expected = false;
            if (is_solution_found.compare_exchange_strong(expected, true)) {
                result = std::make_pair(side_id, t.value());
            }
        }
    }

    return is_solution_found.load() ? std::optional(result) : std::nullopt;
}