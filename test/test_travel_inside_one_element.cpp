#include <iostream>
#include <gtest/gtest.h>
#include <optional>
#include <random>

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

double actual_distance;
double total_track = 0;
double relative_error;


void test_in_voxel_track(int argc, char* argv []){

    libMesh::LibMeshInit init(argc, argv);
    libMesh::Mesh mesh(init.comm());

    libMesh::MeshTools::Generation::build_cube(mesh,24,18,30,0,10,0,10,0,10,libMesh::TET4);
    UnstructuredMesh unstractured_mesh(mesh);

    std::default_random_engine random_number_generator;
    std::uniform_real_distribution <double> distribution (0.01,0.02);

    Point starting_point = {distribution(random_number_generator), distribution(random_number_generator), distribution(random_number_generator)};
    Point destination =  {distribution(random_number_generator), distribution(random_number_generator), distribution(random_number_generator)} ;
    actual_distance = get_distance (starting_point, destination);


    Solver track_length_calculator;
    MiddleEarth gondor(unstractured_mesh, track_length_calculator);
    auto [ids, values]  = gondor.parallelNazgulSolver(starting_point, destination);

    for (auto value:values){
        total_track+=value;
    }

    relative_error = (total_track - actual_distance) * 100 / actual_distance;

}


TEST(track_length_calculation, test_in_voxel_track_calculation) {
    EXPECT_NEAR(actual_distance, total_track, 1e-10);
    EXPECT_NEAR(relative_error, 0, 1e-10);
}


int main(int argc, char **argv) {

    test_in_voxel_track(argc,argv);
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

