#ifndef Material_H
#define Material_H

#include <vector>
#include <string>

class Material
{

public:
    Material(std::string name,
             std::vector<double> &energy_range, std::vector<double>& cross_section);

protected:
    std::string _name;
    std::vector<double> _cross_section; // macroscopic
    std::vector<double> _energy_range;
    unsigned int _number_of_groups;

    // cross section getter
    double getCrossSection(double& energy);
private:
    unsigned int getGroupIndex(double & energy);
};

#endif
