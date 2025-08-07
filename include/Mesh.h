#ifndef SAURON_UNSTRUCTURED_MESH_H
#define SAURON_UNSTRUCTURED_MESH_H

#include <memory>
#include <string>

namespace libMesh {
    class ExodusII_IO;
    class MeshBase;
    class Elem;
    class LibMeshInit;
    class PointLocatorTree;
    class Point;
} // namespace libMesh

namespace sauron {
    struct Point;

    class UnstructuredMesh {
    public:
        // should allow both the case. either read the mesh or get a ref to the mesh
        // from else where
        UnstructuredMesh(std::string &mesh_file_name, libMesh::LibMeshInit &init);
        UnstructuredMesh(libMesh::MeshBase &mesh);

    protected:
        // method for reading the mesh
        libMesh::MeshBase &readMesh(std::string &mesh_file_name);

        // wrapper for libmesh point locator function
        libMesh::Elem *locateElementInMesh(Point &p)const ;
        libMesh::Elem *locateElementInMesh(libMesh::Point &p)const;

    private:
        libMesh::MeshBase &_mesh;
        std::unique_ptr<libMesh::PointLocatorTree> _point_locator;
    };

}

#endif