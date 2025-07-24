#ifndef LIBMESH_TRACK_LENGTH_MESH_H
#define LIBMESH_TRACK_LENGTH_MESH_H


namespace libMesh {
    class DofMap;

    class Elem;

    class EquationSystems;

    class LinearImplicitSystem;

    class MeshBase;

    template<typename T>
    class NumericVector;

    class System;
} ///forward declaration of libMesh classes


class Mesh {
    Mesh(char **argv);

    ///creates a mesh with triangular element
    void createMesh();

    /// create an equation system
    void initiateEquationSystem();

    void writeOutputData(std::string output_file_name);

    libMesh::MeshBase &_mesh;
    libMesh::EquationSystems &_equation_system;
    libMesh::System &_system;
    libMesh::DofMap &_dof_map;

};

#endif
