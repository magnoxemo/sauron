#ifndef Material_H
#define Material_H

#include <vector>
#include <map>
#include <string>
#include <iostream>

class Material
{
public:
    Material(std::map<std::vector<std::string>, std::vector<double>>& cross_section,
             std::map<std::vector<std::string>, std::vector<double>>& energy_range);

    double getCrossSection(std::string& reaction_type, double& energy);
    double getTotalCrossSection(double& energy);

protected:
    std::string _name;
    std::map<std::vector<std::string>, std::vector<double>> _cross_section;
    std::map<std::vector<std::string>, std::vector<double>> _energy_range;
    unsigned int _number_of_groups;

private:
    unsigned int getGroupIndex(std::string& reaction_type, double& energy);
};

#endif

