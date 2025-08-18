#include <iostream>
#include <gtest/gtest.h>
#include <optional>


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


double actual_track_length;
double sauron_calculated_track_length;

void track_length_calculator(int argc, char* argv []){

    libMesh::LibMeshInit init(argc, argv);
    libMesh::Mesh mesh(init.comm());

    libMesh::MeshTools::Generation::build_cube(mesh,5,5,5,0,10,0,10,0,10,libMesh::HEX8);
    //there is a huge issue with what kinda element it can handle
    //for now it's limited with hex only
    UnstructuredMesh unstractured_mesh(mesh);

    //create a ray
    Point starting_point = {2.1,1.34,1.0};
    Point destination = {8,3,2};
    actual_track_length = get_distance (starting_point, destination);


    Solver track_length_calculator;
    MiddleEarth gondor(unstractured_mesh, track_length_calculator);
    auto [ids, values]  = gondor.parallelNazgulSolver(starting_point, destination);

    double total_track = 0;
    for (int i =0; i< ids.size(); i++){
        total_track+=values[i];
    }

    sauron_calculated_track_length = total_track;

}

TEST(track_length_calculation, total_distance_test) {
    EXPECT_NEAR(sauron_calculated_track_length, actual_track_length, 1e-6);
}


int main(int argc, char **argv) {

    track_length_calculator(argc,argv);
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

