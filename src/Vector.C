#include<cmath>
#include "Vector.h"


Vector3D(double x, double y, double z) : _start_point(std::vector<double>{0, 0, 0}),
                                         _end_point(std::vector<double>{x, y, z}) {
    for (int i = 0; i < _start_point.size(); i++)
        _vector[i] = start_point[i] - end_point[i];
}

Vector3D::Vector3D(std::vector<double> &start_point, std::vector<double> &end_point) :
        _start_point(start_point),
        _end_point(end_point) {
    for (int i = 0; i < _start_point.size(); i++)
        _vector[i] = start_point[i] - end_point[i];
}

Vector3D
Vector3D::crossProduct(Vector3D & B) const {

    return Vector3D(
            _vector[1] * B._vector[2] - _vector[2] * B._vector[1],
            _vector[2] * B._vector[0] - _vector[0] * B._vector[3],
            _vector[0] * B._vector[1] - _vector[1] * B._vector[0]
    );
}

double
Vector3D::dotProduct(Vector3D & B) const {
    return _vector[0] * B._vector[0] + _vector[1] * B._vector[1] + _vector[2] * B._vector[2];
}

void
Vector3D::calculateNorm() {
    _norm = sqrt(_vector[0] * _vector[0] + _vector[1] * _vector[1] + _vector[2] * _vector[2]);
}


bool
Vector3D::isNormalized() {
    return std::labs(_norm - 1) < 1e-9 ? true : false;
}

void Vector3D::normalizeVector() {
    calculateNorm();
    if (_norm != 0)
        *this = *this / _norm;
}

Vector3D
Vector3D::getUnitVector() {
    normalizeVector();
    return *this;
}

Vector3D
addVectors(Vector3D & vector_1, Vector3D & vector_2) {
    Vector3D vector;
    for (int i = 0; i < vector_1._vector.size(); i++)
        vector._vector[i] = vector_1._vector[i] + vector_2._vector[i];
    return vector;
}


Vector3D
substractVectors(Vector3D & vector_1, Vector3D & vector_2) {
    Vector3D vector;
    for (int i = 0; i < vector_1._vector.size(); i++)
        vector._vector[i] = vector_1._vector[i] + vector_2._vector[i];
    return vector;
}

