#ifndef PHYSICS_ENGINE_H
#define PHYSICS_ENGINE_H

#include<vector>
#include<string>

#include "material.h"
#include "surface.h"

class Particle{
public:
    Particle(double energy,
             std::vector<double>& position,
             std::vector<double>& _direction)
    std::vector<double>& _position(2);
    std::vector<double>& _direction(2);

protected:
    std::vecotr<double> surfaceCrossingPoint(Surface& surface);

    std::vector<double> computeNewLocation(double& distance);

    std::vector<double> computeNewLocation(double& distance,
                                           std::vector<double> direction);
    //returns the direction of the scattered angle

    void scatteringKernel(Material & mat);

    void samplePostCollisionEnergy(Material& mat);

private:
    double _tolerance = 1e-9;
    bool isDirectionNormalized();
    void normalizeDirection();

};


std::string sampleReactionType(Material);
inline double randomNumberGenerator();


#endif