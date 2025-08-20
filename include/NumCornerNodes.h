#ifndef SAURON_NUMCORNERNODES_H
#define SAURON_NUMCORNERNODES_H

#include "libmesh/elem.h"
/*this is going to be a header only section where I will create a switch
 system to evaluate how many corners are in a 3D libmesh element*/

inline int number_of_corner_nodes_on_a_side(const libMesh::ElemType element_type) {
    switch (element_type) {

        case libMesh::TET4:
            return 3;
        case libMesh::TET10:
            return 3;

        case libMesh::HEX8:
            return 4;
        case libMesh::HEX20:
            return 4;
        case libMesh::HEX27:
            return 4;

        default:
            //should I throw an error this case?
            return -1;
    }
}



#endif
