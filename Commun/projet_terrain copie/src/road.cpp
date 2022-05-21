#include "road.hpp"
#include "terrain.hpp"


using namespace cgp;



mesh create_road_mesh(float terrain_length){

    mesh m;

    // Number of samples
    int N = 50;

    m.position.resize(2*N+2);
    m.uv.resize(2*N+2);
    
    // Geometry
    for(int k=0; k<N+1; ++k)
    {
        float l = (float) k/float(N);
        vec3 p = {-10+ 0.1f * noise_perlin({ -10/3.0f + 50, (l-0.5f)*terrain_length/3.0f +50 }, 4, 0.35, 2.0), (l-0.5f)*terrain_length, evaluate_terrain_height(-10, (l-0.5f)*terrain_length) +0.01f};
        vec3 q = {-11+ 0.1f * noise_perlin({ -11/3.0f + 50, (l-0.5f)*terrain_length/3.0f +50 }, 4, 0.35, 2.0), (l-0.5f)*terrain_length, evaluate_terrain_height(-11, (l-0.5f)*terrain_length)+0.01f};
        //m.position.push_back(p);
        //m.position.push_back(q);
        m.position[2*k]= p;
        m.position[2*k+1]= q;
        m.uv[2*k]= {1, 50*l};
        m.uv[2*k+1]= {0, 50*l};
    }
    
    // Connectivity
    for(int k=0; k<N; ++k)
    {
        int u00 = 2*k;
        int u01 = (2*k+1);
        int u10 = (2*(k+1));
        int u11 = (2*(k+1)+1);

        uint3 t1 = {u00, u10, u11};
        uint3 t2 = {u00, u11, u01};
        m.connectivity.push_back(t1);
        m.connectivity.push_back(t2);
    }

    m.fill_empty_field();
    return m;
}

std::vector<vec3> generate_positions_on_road(int N, float terrain_length)
{
    std::vector<cgp::vec3> position;
    for (int k = 0; k < N; ++k)
    {
        float const x = -10.5f;
        float const y = (0.98*rand_interval()-0.45f) * terrain_length;

        vec3 const p = { x, y, evaluate_terrain_height(x,y) + 0.01f };

        bool to_add = true;
        for (int k2 = 0; to_add==true && k2 < position.size(); ++k2) {
            vec3 const& p2 = position[k2];
            if(norm(p2-p)<0.8f)
                to_add=false;
        }
        if(to_add)
            position.push_back(p);
    }
    return position;
}


