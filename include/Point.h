#ifndef SAURON_POINT_H
#define SAURON_POINT_H


namespace sauron{

    // making a Point struct for my own sanity
    struct Point {
        double x, y, z;

        // Overloading the addition operator (+)
        Point operator+( Point &other) const {
            return {x + other.x, y + other.y, z + other.z};
        }
        // Overloading the addition operator (+)
        Point operator+( double t) const {
            return {x +t, y +t, z +t};
        }

        // Overloading the addition operator (+)
        Point operator-( Point &other) const {
            return {x - other.x, y - other.y, z - other.z};
        }

        Point operator -(const double t) const {
            return {x - t, y - t, z - t};
        }

        // Overloading the addition operator (+)
        Point operator*(const Point &other) const {
            return {x * other.x, y * other.y, z * other.z};
        }

        Point operator*( double t) const {
            return {x * t, y * t, z * t};
        }

        // Overloading the addition operator (+)
        Point operator/( Point &other) const {
            return {x / other.x, y / other.y, z / other.z};
        }

        Point operator/( double t) const {
            return {x / t, y / t, z / t};
        }
        // Overloading the equality operator (==)
        bool operator==( Point &other) const {
            return (x == other.x && y == other.y && z == other.z );
        }

    };
}


#endif
