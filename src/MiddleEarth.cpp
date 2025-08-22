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

  // TODO :
  // libmesh stores the corner nodes first then then the other nodes. so I can
  // just store the n corner nodes and then do triangle solve. that way sauron
  // can support other elements as well
  //  rather than push it back I need to fix the vector size at once
  vertices_on_this_side.clear();

  auto num_corner_nodes = number_of_corner_nodes_on_a_side(element->type());
  if (num_corner_nodes!=-1){
    vertices_on_this_side.resize(num_corner_nodes);
    auto nodes = element->nodes_on_side(side_id);
    for (decltype(num_corner_nodes) node_index =0 ; node_index<num_corner_nodes; node_index++) {
      auto p = element->point(nodes[node_index]);
      vertices_on_this_side[node_index] = sauron::convertLibMeshPointToSauronPoint(p);
    }
  }
  else{
    std::cerr<<"Unsupported element type"<<element->type();
  }
  vertices_on_this_side.shrink_to_fit();

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
  // if both elements are same then no need solve those repeately
  if (starting_element == destination_element) {

    auto [forward_side_id, forward_ray_segment] = std::make_pair(
        starting_element->id(), get_distance(current_point, destination_point));
    intercepted_element_ids.push_back(forward_side_id);
    ray_segments.push_back(forward_ray_segment);
    // should I add any check if track length == dist?
    return std::make_pair(intercepted_element_ids, ray_segments);
  }

  auto forward_direction = destination_point - current_point;
  auto reverse_direction = current_point - destination_point;

  sauron::Ray forward_ray(current_point, forward_direction);
  sauron::Ray backward_ray(destination_point, reverse_direction);

  double total_track_length =
      sauron::get_distance(current_point, destination_point);
  double dist = 0.0;

  while (dist <= total_track_length) {
    //      std::cout<<"solving starting element id = "
    //      <<starting_element->id()<<" and destination element id =
    //      "<<destination_element->id()<<"\n";

    auto forward_solution = solveOneElement(forward_ray, starting_element);
    auto reverse_solution = solveOneElement(backward_ray, destination_element);

    bool progress_made = false;

    if (forward_solution) {
      auto [forward_side_id, forward_ray_segment] = forward_solution.value();
      intercepted_element_ids.push_back(starting_element->id());
      ray_segments.push_back(forward_ray_segment);
      dist += forward_ray_segment;
      starting_element = starting_element->neighbor_ptr(forward_side_id);
      forward_ray._starting_point =
          forward_ray._starting_point +
          forward_ray._direction * forward_ray_segment;
      progress_made = true;
    }


    if (reverse_solution) {
      auto [reverse_side_id, reverse_ray_segment] = reverse_solution.value();
      intercepted_element_ids.push_back(destination_element->id());
      ray_segments.push_back(reverse_ray_segment);
      dist += reverse_ray_segment;
      destination_element = destination_element->neighbor_ptr(reverse_side_id);
      backward_ray._starting_point =
          backward_ray._starting_point +
          backward_ray._direction * reverse_ray_segment;
      progress_made = true;
    }


    if (!progress_made ||
        (backward_ray._starting_point == forward_ray._starting_point))
      break; // need to come up with better way to avoid infinte loop
  }

  return std::make_pair(intercepted_element_ids, ray_segments);
}

std::optional<std::pair<unsigned int, double>>
sauron::MiddleEarth::solveOneElement(sauron::Ray &ray,
                                     const libMesh::Elem *element) {

  std::atomic<bool> is_solution_found(false);
  std::pair<unsigned int, double> result;
  const unsigned int num_sides = element->n_sides();

  omp_set_num_threads(num_sides);
#pragma omp parallel for default(none)                                         \
    shared(num_sides, is_solution_found, result, ray, element)                 \
    schedule(dynamic)
  for (unsigned int side_id = 0; side_id < num_sides; ++side_id) {
    if (is_solution_found.load())
      continue;

    std::vector<sauron::Point> vertices_on_this_side;
    get_nodes_on_a_side(element, side_id, vertices_on_this_side);

    std::optional<double> t;
    try {
      if (vertices_on_this_side.size() == 3) {
        t = _solver.triangleSolver(ray, vertices_on_this_side);
        //        std::cout<<"caling triangle solver\n";
      } else if (vertices_on_this_side.size() == 4) {
        t = _solver.quadSolver(ray, vertices_on_this_side);
        //        std::cout<<"caling quad solver\n";
      }
    } catch (...) {
      continue;
    }

    if (t.has_value()) {
      //      std::cout<<"track "<<t.value()<<"\n";
      bool expected = false;
      if (is_solution_found.compare_exchange_strong(expected, true)) {
        result = std::make_pair(side_id, t.value());
      }
    }
  }

  return is_solution_found.load() ? std::optional(result) : std::nullopt;
}