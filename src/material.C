#include<iostream>

#include "material.h"

Material::Material(std::string name,
    std::vector<double> &energy_range, std::vector<double>& cross_section):
    _name(name),
    _energy_range(energy_range),
    _cross_section(cross_section),
    _number_of_groups(cross_section.size())
{
    if (_number_of_groups!=_energy_range.size()-1){
        std::cerr<<"energy range needs to be 1 more than number of groups\n";
    }
}
        

double
Material::getCrossSection(double& energy){

}

unsigned int 
Material::getGroupIndex(double& energy){
    
    if (energy<0)
        std::cerr<<"Energy can't be negative";

    if (energy<_energy_range[0])
        return 0;

    for (int i =1 ; i<_energy_range.size();i++){
        if ((_energy_range[i-1]<energy) && (_energy_range[i]>energy))
            return i;
    }
    return -1; // range  not found 
}