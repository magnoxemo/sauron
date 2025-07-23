#ifndef LIBMESH_TRACK_LENGTH_VECTOR_H
#define LIBMESH_TRACK_LENGTH_VECTOR_H

#include <vector>
#include <cstdlib>
#include <iostream>

namespace Bijorn {
    class Vector3D {

    public:
        Vector3D() : _vector{0, 0, 0}, _norm(0) {}

        Vector3D(double x, double y, double z);

        Vector3D(std::vector<double> &start_point, std::vector<double> &end_point);

        inline double getVectorComponent(unsigned int index) const {
            return _vector[index];
        }

        inline void setVectorComponent(double value, unsigned int index) {
            _vector[index] = value;
        }

        Vector3D crossProduct(Vector3D &B)const;

        double dotProduct(Vector3D &B) const ;

        void calculateNorm();
        double calculateNorm();

        Vector3D getUnitVector();

        bool isNormalized();

        void normalizeVector();

        Vector3D &operator+(double t) {
            for (int i = 0; i < _vector.size(); i++)
                _vector[i] = _vector[i] + t;
            return *this;

        }

        Vector3D &operator-(double t) {
            for (int i = 0; i < _vector.size(); i++)
                _vector[i] = _vector[i] - t;
            return *this;

        }

        Vector3D &operator*(double t) {
            for (int i = 0; i < _vector.size(); i++)
                _vector[i] = _vector[i] * t;
            return *this;
        }

        Vector3D &operator/(double t) {
            if (t == 0)
                std::cerr << "division error";
            for (int i = 0; i < _vector.size(); i++)
                _vector[i] = _vector[i] / t;
            return *this;
        }

        std::vector<double> _vector(

        3);

        std::vector<double> _start_point(

        3);

        std::vector<double> _end_point(

        3);
        double _norm;
    };

    using Point = Vector3D;

    Vector3D addVectors(Vector3D &vector_1, Vector3D &vector_2);

    Vector3D substractVectors(Vector3D &vector_1, Vector3D &vector_2);
}

#endif
