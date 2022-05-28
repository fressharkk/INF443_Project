#include "cart.hpp"


using namespace cgp;

mesh create_cart_mesh(float terrain_length){

    mesh m;

    m = mesh_load_file_obj("assets/cart.obj");
    return m;
}


