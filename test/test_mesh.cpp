#include "libmesh/libmesh.h"
#include "libmesh/mesh.h"
#include "libmesh/mesh_generation.h"
#include "libmesh/point.h"
#include "libmesh/elem.h"

#include <cmath>
#include <gtest/gtest.h>
#include <iostream>

#include "Mesh.h"
#include "Point.h"
#include "Logo.h"

using namespace sauron;

const libMesh::Elem* element_via_sauron_point;
const libMesh::Elem* element_via_libmesh_point;

void
test_point_locator(int argc, char* argv []){

    libMesh::LibMeshInit init(argc, argv);
    libMesh::Mesh mesh(init.comm());

    libMesh::MeshTools::Generation::build_square(mesh,10,10,0,10,0,10);
    UnstructuredMesh test_mesh(mesh);

    Point sauron_point = {0,0,0};
    libMesh::Point libmesh_point  (0,0,0);
    element_via_sauron_point = test_mesh.locateElementInMesh(sauron_point);
    element_via_libmesh_point = test_mesh.locateElementInMesh(libmesh_point);

}
/*this test checks if the conversation between sauron point and libmesh point works
 *if both case can locate the same element in the mesh
 *if both are the same element ptr*/
TEST(element_test, same_element_locate_test){

    //maybe i need to learn a better way to write test in these cases
    ASSERT_NE(element_via_sauron_point, nullptr);
    ASSERT_NE(element_via_libmesh_point, nullptr);
    EXPECT_EQ(true, element_via_sauron_point->id() == element_via_libmesh_point->id());

}

int main(int argc, char **argv) {

    test_point_locator(argc,argv);
    printLogo();
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
