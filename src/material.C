#include<iostream>

#include "material.h"

Material::Material(std::map<std::vector<std::string>, std::vector<double>>& cross_section,
                   std::map<std::vector<std::string>, std::vector<double>>& energy_range)
        : _cross_section(cross_section), _energy_range(energy_range)
{

    if (!cross_section.empty())
    {
        _number_of_groups = cross_section.begin()->second.size();
    }
    else
    {
        _number_of_groups = 0;
    }
}

double
Material::double getCrossSection(std::string& reaction_type, double& energy)
{
    unsigned int idx = getGroupIndex(reaction_type, energy);
    for (const auto& entry : _cross_section)
    {
        if (entry.first[0] == reaction_type)
        {
            return entry.second[idx];
        }
    }
    return 0.0;
}

unsigned int
Material::getGroupIndex(std::string& reaction_type, double& energy)
{
    for (const auto& entry : _energy_range)
    {
        if (entry.first[0] == reaction_type)
        {
            const std::vector<double>& boundaries = entry.second;
            for (unsigned int i = 0; i < boundaries.size() - 1; ++i)
            {
                if (energy >= boundaries[i] && energy < boundaries[i + 1])
                {
                    return i;
                }
            }
        }
    }
    return _number_of_groups - 1;
}

double
Material::getTotalCrossSection(double& energy){
    double total_cross_section = 0;
    for (const auto & entry : _energy_range){
        total_cross_section+=getCrossSection(entry.first[0], energy);
    }
    return total_cross_section;
}