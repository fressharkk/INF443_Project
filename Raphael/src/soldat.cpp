#include "cart.hpp"


using namespace cgp;

mesh create_soldat_mesh(){

    mesh m;

    m = mesh_load_file_obj("assets/soldat_2.obj");
    return m;
}


