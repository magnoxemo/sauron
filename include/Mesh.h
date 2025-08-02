#include <string>
#include <iostream>
#include <stdexcept>


namespace libMesh{
    class ExodusII_IO;
    class MeshBase;
    class Elem;
}//forward declaration


namespace sauron{

    struct Point;



    class UnstructedMesh{
        UnstructedMesh(std::string& mesh_file_name , libMesh::LibMeshInit& init):
            _meshinit(.comm()),
            _exodus_io(_mesh)

        {
            //try to read the mesh first
            try{
                _exodus_io.read(mesh_file_name);
                _mesh.print_info();
            }catch (const std::exception& error)
                std::cerr<< "Error reading the "<<mesh_file_name<<" \n"<< error.what()<<std::endl;


        }

        //wrapper for libmesh point locator function
        libMesh::Elem* locateElementInMesh(Point& p);

        //should I make it a static ref? There is no need to copy it since mc would have it anyway.
        libMesh::MeshBase& _mesh;
        libMesh::ExodusII_IO& _exodus_io;

    };
}
