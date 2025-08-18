#include <iostream>

#include "Solver.h"
#include "Point.h"
#include "MiddleEarth.h"
#include "Ray.h"
#include "Mesh.h"


#include "libmesh/libmesh.h"
#include "libmesh/mesh.h"
#include "libmesh/mesh_generation.h"
#include "libmesh/point.h"
#include "libmesh/elem.h"

using namespace sauron;

int main(int argc, char* argv []){

    libMesh::LibMeshInit init(argc, argv);
    libMesh::Mesh mesh(init.comm());

    libMesh::MeshTools::Generation::build_cube(mesh,10,10,10,0,10,0,10,0,10,libMesh::HEX8);
    //there is a huge issue with what kinda element it can handle
    //for now hex8 is working ig
    //TO DO:
    // - enable support for all 3D elements.
    // - way to determine only the edge nodes in a side
    UnstructuredMesh unstractured_mesh(mesh);

    //create a ray
    Point starting_point = {0,0,0};
    Point destination = {1,10,2};
    auto distance = get_distance (starting_point, destination);


    Solver track_length_calculator;
    MiddleEarth gondor(unstractured_mesh, track_length_calculator);
    auto [ids, values]  = gondor.parallelNazgulSolver(starting_point, destination);

    double total_track = 0;
    for (int i =0; i< ids.size(); i++){
        total_track+=values[i];
    }

    std::cout<<distance<< " track "<<total_track<<std::endl;

    return 0;
}