#include <iostream>

#include "Logo.h"
#include "Mesh.h"
#include "Point.h"
#include "Ray.h"


#include "libmesh/libmesh.h"
#include "libmesh/mesh.h"
#include "libmesh/point.h"
#include "libmesh/exodusII_io.h"
#include "libmesh/point_locator_tree.h"
#include "libmesh/elem.h"



sauron::UnstructuredMesh::UnstructuredMesh(std::string& mesh_name, libMesh::LibMeshInit& init):
        _mesh(readMesh(mesh_name)),
        _point_locator(std::make_unique<libMesh::PointLocatorTree>(_mesh))
{
}

sauron::UnstructuredMesh::UnstructuredMesh(libMesh::MeshBase& mesh):
        _mesh(mesh),
        _point_locator(std::make_unique<libMesh::PointLocatorTree>(_mesh))
{
}

libMesh::MeshBase&
sauron::UnstructuredMesh::readMesh(std::string& mesh_name){
    //try to read the mesh first
    try{
        libMesh::ExodusII_IO exio(_mesh);
        exio.read(mesh_name);
        _mesh.print_info();
    }
    catch (const std::exception& error){
        std::cerr<< "Error reading the "<<mesh_name<<" \n"<< error.what()<<std::endl;
    }

    return _mesh;
}

libMesh::Elem *
sauron::UnstructuredMesh::locateElementInMesh(sauron::Point &p){
    //now that point isn't a libmesh point. So I have to convert it first

    const libMesh::Point point (p.x, p.y, p.z);
    return locateElementInMesh(point);

}

libMesh::Elem *
sauron::UnstructuredMesh::locateElementInMesh(libMesh::Point &p){
    return (* _point_locator) (point);
}


