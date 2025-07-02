#include<cstdlib>
#include<random>

#include "physics_engine.h"

Particle::Particle(double energy,
                   std::vector<double>& position,
                   std::vector<double>& direction):
                   _energy(energy),
                   _position(position),
                   _direction(direction){

    if (_position.size()!=2)
        std::cerr<<"3D transport not supported\n";

    if (_energy<0)
        std::cerr<<"Negative energy not allowed\n";

    if ( !isDirectionNormalized() )
        normalizeDirection();
}

bool
Particle::isDirectionNormalized(){

    if (std::fabs((_direction[0]*_direction[0]+_direction[1]*_direction[1])-1)<_tolerance){
        return true;
    }
    return false;
}

void
Particle::normalizeDirection(){
    double norm = _direction[0]*_direction[0]+_direction[1]*_direction[1];
    for (int i =0; i<_direction.size();i++){
        _direction [i] = _direcion[i]/norm;
    }

}

void
Particle::scatteringKernel(Material& material){


}

inline double
randomNumberGenerator(){
    return static_cast<double> (rand()/RAND_MAX);
}