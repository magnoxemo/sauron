#include "libmesh/point.h"
#include "Point.h"


sauron::Point
sauron::convertLibMeshPointToSauronPoint(libMesh::Point& point){
    sauron::Point p = {point(0), point(1), point(2)};
    return p;
}

sauron::Point
sauron::cross_product(const Point& point_a, const Point& point_b){

    return {
            point_a.y * point_b.z - point_a.z * point_b.y,
            point_a.z * point_b.x - point_a.x * point_b.z,
            point_a.x * point_b.y - point_a.y * point_b.x
    };
}

double
sauron::dot_product(const Point& point_a, const Point& point_b){
    return (point_a * point_b).sum();
}

double
sauron::get_distance(const Point& point_a, const Point& point_b){

    auto l = point_a - point_b;
    return sqrt((l*l).sum());
}
