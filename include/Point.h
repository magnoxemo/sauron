#ifndef SAURON_POINT_H
#define SAURON_POINT_H

#include "libmesh/point.h"

namespace sauron{


    // making a Point struct for my own sanity
    struct Point {
        double x, y, z;

        // Overloading the addition operator (+)
        Point operator+(const  Point &other) const {
            return {x + other.x, y + other.y, z + other.z};
        }
        // Overloading the addition operator (+)
        Point operator+( double t) const {
            return {x +t, y +t, z +t};
        }

        // Overloading the addition operator (+)
        Point operator-(const Point &other) const {
            return {x - other.x, y - other.y, z - other.z};
        }

        Point operator -( double t) const {
            return {x - t, y - t, z - t};
        }

        // Overloading the addition operator (+)
        Point operator*( const Point &other) const {
            return {x * other.x, y * other.y, z * other.z};
        }

        Point operator*(double t) const {
            return {x * t, y * t, z * t};
        }

        // Overloading the addition operator (+)
        Point operator/(const Point &other) const {
            return {x / other.x, y / other.y, z / other.z};
        }

        Point operator/( double t) const {
            return {x / t, y / t, z / t};
        }
        // Overloading the equality operator (==)
        bool operator==( const Point &other) const {
            return (x == other.x && y == other.y && z == other.z );
        }

        double sum()const {
            return x+y+z;
        }

    };

    Point convertLibMeshPointToSauronPoint(libMesh::Point& point){
        sauron::Point p = {point(0), point(1), point(2)};
        return p;
    }

    Point cross_product(const Point& point_a, const Point& point_b){

        return {
                point_a.y * point_b.z - point_a.z * point_b.y,
                point_a.z * point_b.x - point_a.x * point_b.z,
                point_a.x * point_b.y - point_a.y * point_b.x
        };
    }
    Point dot_product(const Point& point_a, const Point& point_b){
        return point_a * point_b;
    }
}





#endif
